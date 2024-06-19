#include "Simulator.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

Simulator::Simulator(std::shared_ptr<Micromouse> mmouse) : micromouse(mmouse), startX(1), startY(1){
    maze = std::make_shared<Maze>(3, 3, "logs/maze.log");
    maze->displayMaze();
}

void Simulator::run() {
    setRandomStartPosition();
    collisionCount=0;
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
    // micromouse->saveRouteToFile("logs/mouse_route.txt");
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
    auto grid = maze->getMazeGrid();
    int mouseX = micromouse->getPosX();
    int mouseY = micromouse->getPosY();

    for (int y = 0; y < grid[0].size(); ++y) {
        for (int x = 0; x < grid.size(); ++x) {
            if (x == mouseX && y == mouseY) {
                std::cout << 'M' << ' ';
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
    
    // Check if the new position is a wall
    if (maze->isWall(currentX, currentY)) {
        std::cout << "Collision with wall at (" << currentX << ", " << currentY << "). Reverting to (" << previousX << ", " << previousY << ").\n";
        // Revert to the previous position
        micromouse->setPosition(previousX, previousY);
        collisionCount++;
        std::cout << "Collision count: " << collisionCount << "\n";
    } else {
        std::cout << "Moved to (" << currentX << ", " << currentY << ").\n";
    }

    if (collisionCount >= 3) {
        std::cout << "Micromouse died after 3 collisions with walls.\n";
        exit(0); // Exit the program
    }
}

// void Simulator::reset() {
//     micromouse->setPosition(startX, tartY);
// }
