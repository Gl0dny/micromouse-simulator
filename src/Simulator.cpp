#include "Simulator.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

Simulator::Simulator(std::shared_ptr<Micromouse> micromouse, std::shared_ptr<Maze> maze) : micromouse(micromouse), maze(maze), startX(1), startY(1) {}

void Simulator::run() {
    setRandomStartPosition();
    collisionCount = 0;
    while (!hasReachedGoal()) {
        int previousX = micromouse->getPosX();
        int previousY = micromouse->getPosY();
        displayMazeWithMouse();
        micromouse->move(); // Move based on the current direction
        checkAndHandleWallCollision(previousX, previousY); // Check for wall collision

        // Delay for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    displayMazeWithMouse();
    std::cout << "Micromouse escaped from the Maze!\n";
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
}

void Simulator::displayMazeWithMouse() const {
    auto grid = micromouse->getKnownMaze();
    int mouseX = micromouse->getPosX();
    int mouseY = micromouse->getPosY();

    for (int y = 0; y < grid[0].size(); ++y) {
        for (int x = 0; x < grid.size(); ++x) {
            if (x == mouseX && y == mouseY) {
                std::cout << 'M' << ' ';
            } else if (grid[x][y] == -1) {
                std::cout << '?' << ' ';
            } else {
                std::cout << (grid[x][y] ? '#' : ' ') << ' ';
            }
        }
        std::cout << '\n';
    }
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
        std::cout << "Collision with wall at (" << currentX << ", " << currentY << "). Reverting to (" << previousX << ", " << previousY << ").\n";
        micromouse->setPosition(previousX, previousY);
        collisionCount++;
        std::cout << "Collision count: " << collisionCount << "\n";
    } else {
        std::cout << "Moved to (" << currentX << ", " << currentY << ").\n";
    }

    if (collisionCount >= 3) {
        std::cout << "Micromouse died after 3 collisions with walls.\n";
        exit(0);
    }
}
