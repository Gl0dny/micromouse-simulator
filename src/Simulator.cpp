#include "Simulator.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>

Simulator::Simulator(std::shared_ptr<Micromouse> micromouse, Maze* maze) 
    : micromouse(micromouse), maze(maze), startX(1), startY(1), steps(0), running(false) {
        totalSeconds = std::chrono::duration<double>::zero(); 
        startTime = std::chrono::steady_clock::time_point::min(); // Initialize with "zero" time
        setRandomStartPosition();
    }

void Simulator::run() {
    running = true;

    // Only set startTime if it is not already set
    if (startTime == std::chrono::steady_clock::time_point::min()) {
        startTime = std::chrono::steady_clock::now();
    }

    while (running && !hasReachedGoal()) {
        int previousX = micromouse->getPosX();
        int previousY = micromouse->getPosY();
        displayMazeWithMouse();
        micromouse->move();
        steps++;
        checkAndHandleWallCollision(previousX, previousY);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    
    if (hasReachedGoal()) {
        std::cout << "Micromouse escaped from the Maze!\n";
        displayMazeWithMouse();
        auto endTime = std::chrono::steady_clock::now();
        totalSeconds = endTime - startTime;
        std::cout << "Total steps taken: " << steps << "\n";
        std::cout << "Total simulation time: " << totalSeconds.count() << " seconds\n";
        exit(0);
    } else {
        std::cout << "Simulation paused before the Micromouse could escape.\n";
    }
}

void Simulator::setRandomStartPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int corner = dis(gen);

    switch (corner) {
        case 0:
            startX = 1;
            startY = 1;
            break;
        case 1:
            startX = maze->getWidth() - 2;
            startY = 1;
            break;
        case 2:
            startX = 1;
            startY = maze->getHeight() - 2;
            break;
        case 3:
            startX = maze->getWidth() - 2;
            startY = maze->getHeight() - 2;
            break;
        default:
            throw std::invalid_argument("Invalid corner specified");
    }
    std::cout << "Micromouse starting at (" << startX << ", " << startY << ").\n";
    micromouse->setPosition(startX, startY);
    displayMazeWithMouse();
}

void Simulator::displayMazeWithMouse() const {
    auto grid = micromouse->getKnownMaze();
    int mouseX = micromouse->getPosX();
    int mouseY = micromouse->getPosY();

    // Log each row of the maze with mouse position
    for (int y = grid[0].size() - 1; y >= 0; --y) {
        std::string rowString;
        for (int x = 0; x < grid.size(); ++x) {
            if (x == mouseX && y == mouseY) {
                rowString += 'M';
            } else if (grid[x][y] == -1) {
                rowString += '?';
            } else if (grid[x][y] == 1) {
                rowString += '#';
            } else {
                rowString += ' ';
            }
            rowString += ' ';
        }
        std::cout << rowString << std::endl;
    }
    std::cout << "Steps taken: " << steps << "\n";
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> totalSeconds = currentTime - startTime;
    std::cout << "Simulation time: " << totalSeconds.count() << " seconds\n";
    std::cout << std::endl;
}

bool Simulator::hasReachedGoal() const {
    auto [exitX, exitY] = maze->readExit();
    return micromouse->getPosX() == exitX && micromouse->getPosY() == exitY;
}

void Simulator::checkAndHandleWallCollision(int previousX, int previousY) {
    int currentX = micromouse->getPosX();
    int currentY = micromouse->getPosY();
    if (maze->isWall(currentX, currentY)) {
        std::cout << "Collision with wall at (" << currentX << ", " << currentY << ").\n";
        std::cout << "Micromouse died after a collision with walls.\n";
        running = false;
    }
}

void Simulator::start() {
    if (!running) {
        std::thread(&Simulator::run, this).detach();
    }
}

void Simulator::pause() {
    running = false;
    std::cout << "Simulation paused. You can reset it by entering 'reset' or unpause by entering 'start'\n";
}

void Simulator::reset() {
    if (!running) {
        steps = 0;
        startTime = std::chrono::steady_clock::time_point::min();
        totalSeconds = std::chrono::duration<double>::zero(); 
        micromouse->reset(); 
        setRandomStartPosition();
        std::cout << "Simulation has been reset. You can start with 'start'.\n";
    } else {
        std::cout << "Cannot reset while the simulation is running. Please pause the simulation first.\n";
    }
}
