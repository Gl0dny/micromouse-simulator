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

RightHandRuleMazeSolver::RightHandRuleMazeSolver()
    : Micromouse() {}

void RightHandRuleMazeSolver::makeDecision() {
    static const std::map<std::string, std::pair<int, int>> directions = {
        {"North", {0, 1}}, {"East", {1, 0}}, {"South", {0, -1}}, {"West", {-1, 0}}
    };

    static const std::map<std::string, std::string> rightTurns = {
        {"North", "East"}, {"East", "South"}, {"South", "West"}, {"West", "North"}
    };

    static const std::map<std::string, std::string> leftTurns = {
        {"North", "West"}, {"West", "South"}, {"South", "East"}, {"East", "North"}
    };

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
            auto [ldx, ldy] = directions.at(newDirection);
            if (knownMaze[posX + ldx][posY + ldy] != 1) {
                direction = newDirection;
            } else {
                // Turn around
                newDirection = leftTurns.at(leftTurns.at(direction));
                direction = newDirection;
            }
        }
    }
}


BacktrackingMazeSolver::BacktrackingMazeSolver()
    : Micromouse() {}

void BacktrackingMazeSolver::makeDecision() {
    // Implement the backtracking logic
}

std::shared_ptr<Micromouse> chooseMicromouse(std::shared_ptr<Maze> maze) {
    int solverChoice, sensorChoice;
    std::cout << "Choose Micromouse type:\n1. Right Hand Rule\n2. Backtracking\n";
    std::cin >> solverChoice;
    std::cout << "Choose Sensor type:\n1. Distance Sensor\n2. Laser Sensor\n3. Lidar Sensor\n";
    std::cin >> sensorChoice;

    switch (solverChoice) {
        case 1:
            switch (sensorChoice) {
                case 1:
                    return createMicromouse<RightHandRuleMazeSolver, DistanceSensor>(maze);
                case 2:
                    return createMicromouse<RightHandRuleMazeSolver, LaserSensor>(maze);
                case 3:
                    return createMicromouse<RightHandRuleMazeSolver, LidarSensor>(maze);
                default:
                    std::cerr << "Invalid sensor choice" << std::endl;
                    return nullptr;
            }
        case 2:
            switch (sensorChoice) {
                case 1:
                    return createMicromouse<BacktrackingMazeSolver, DistanceSensor>(maze);
                case 2:
                    return createMicromouse<BacktrackingMazeSolver, LaserSensor>(maze);
                case 3:
                    return createMicromouse<BacktrackingMazeSolver, LidarSensor>(maze);
                default:
                    std::cerr << "Invalid sensor choice" << std::endl;
                    return nullptr;
            }
        default:
            std::cerr << "Invalid solver choice" << std::endl;
            return nullptr;
    }
}