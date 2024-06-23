#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse() : posX(1), posY(1), direction("North") {}

void Micromouse::setSensor(std::shared_ptr<Sensor> sensor) {
    this->sensor = sensor;
}

int Micromouse::getPosX() const {
    return posX;
}

int Micromouse::getPosY() const {
    return posY;
}

void Micromouse::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void Micromouse::move() {
    readSensors();
    makeDecision();
    if (direction == "North") {
        posY++;
    } else if (direction == "East") {
        posX++;
    } else if (direction == "South") {
        posY--;
    } else if (direction == "West") {
        posX--;
    }
}

void Micromouse::readSensors() {
    sensor->getSensorData(posX, posY, knownMaze);
}

void Micromouse::initializeKnownMaze(int width, int height) {
    knownMaze = std::vector<std::vector<int>>(width, std::vector<int>(height, -1));
}

std::vector<std::vector<int>> Micromouse::getKnownMaze() const {
    return knownMaze;
}

void Micromouse::reset() {
    posX = 1;
    posY = 1;
    direction = "North";
    for (auto& row : knownMaze) {
        std::fill(row.begin(), row.end(), -1);
    }
}

RightHandRuleBacktrackingMazeSolver::RightHandRuleBacktrackingMazeSolver()
    : Micromouse() {}

void RightHandRuleBacktrackingMazeSolver::makeDecision() {

    std::string newDirection = rightTurns.at(direction);
    auto [dx, dy] = directions.at(newDirection);

    // Check if right-hand side is free
    if (knownMaze[posX + dx][posY + dy] != 1) {
        direction = newDirection;
    } else {
        // Check current direction
        auto [dx, dy] = directions.at(direction);
        if (knownMaze[posX + dx][posY + dy] == 1) {
            // Check left-hand side
            newDirection = leftTurns.at(direction);
            auto [dx, dy] = directions.at(newDirection);
            if (knownMaze[posX + dx][posY + dy] != 1) {
                direction = newDirection;
            } else {
                // Turn around
                newDirection = leftTurns.at(leftTurns.at(direction));
                direction = newDirection;
            }
        }
    }
}

std::shared_ptr<Micromouse> chooseMicromouse(Maze* maze) {
    int solverChoice, sensorChoice;
    std::cout << "Choose Micromouse type:\n1. Right Hand Rule\n";
    std::cin >> solverChoice;
    std::cout << "Choose Sensor type:\n1. Distance Sensor\n2. Laser Sensor\n3. Lidar Sensor\n";
    std::cin >> sensorChoice;

    switch (solverChoice) {
        case 1:
            switch (sensorChoice) {
                case 1:
                    return createMicromouse<RightHandRuleBacktrackingMazeSolver, DistanceSensor>(maze);
                case 2:
                    return createMicromouse<RightHandRuleBacktrackingMazeSolver, LaserSensor>(maze);
                case 3:
                    return createMicromouse<RightHandRuleBacktrackingMazeSolver, LidarSensor>(maze);
                default:
                    std::cerr << "Invalid sensor choice" << std::endl;
                    return nullptr;
            }
        default:
            std::cerr << "Invalid solver choice" << std::endl;
            return nullptr;
    }
}