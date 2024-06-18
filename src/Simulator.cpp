#include "Simulator.h"
#include <iostream>
#include <random>

Simulator::Simulator(Micromouse& mmouse) : micromouse(mmouse) {
    maze = std::make_shared<Maze>(21, 21, "logs/maze.log");
    maze->displayMaze();
}

void Simulator::run() {
    // setRandomMouseStartPosition();

    // while (!micromouse.hasReachedGoal()) {
    //     micromouse.updateSensors();
    //     micromouse.makeDecision();
        displayMazeWithMouse();
    // }
    // micromouse.saveRouteToFile("mouse_route.txt");
}

void Simulator::setRandomStartPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int corner = dis(gen);

    int startX, startY;
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
    micromouse.setStartingPosition(startX, startY);
}


void Simulator::displayMazeWithMouse() const {
    auto grid = maze->getMazeGrid();
    int mouseX = micromouse.getPosX();
    int mouseY = micromouse.getPosY();

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
