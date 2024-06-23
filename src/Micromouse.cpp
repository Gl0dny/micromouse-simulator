#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse(const std::string& logFileName)
    : posX(1), posY(1), direction("North"), step(0), logger(std::make_unique<Logger>("logs/" + logFileName + ".log")) {
    logger->enableFileOutput();
    logger->clearLogFile();
}

void Micromouse::setSensor(std::shared_ptr<Sensor> sensor) {
    this->sensor = sensor;
    logger->logMessage("Sensor set for Micromouse");
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
    logger->logMessage("Step " + std::to_string(step) + ": Micromouse position set to (" + std::to_string(x) + "," + std::to_string(y) + ")");
}

void Micromouse::move() {
    step++;
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
    logger->logMessage("Step " + std::to_string(step) + ": Micromouse moved to (" + std::to_string(posX) + "," + std::to_string(posY) + ") facing " + direction);
}

void Micromouse::readSensors() {
    sensor->getSensorData(posX, posY, knownMaze, step);
    logger->logMessage("Step " + std::to_string(step) + ": Sensors read at position (" + std::to_string(posX) + "," + std::to_string(posY) + ")");
}

int Micromouse::getStep() const {
    return step;
}

void Micromouse::initializeKnownMaze(int width, int height) {
    knownMaze = std::vector<std::vector<int>>(width, std::vector<int>(height, -1));
    logger->logMessage("Known maze initialized with dimensions (" + std::to_string(width) + "," + std::to_string(height) + ")");
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
    logger->logMessage("Micromouse reset to initial state");
}

RightHandRuleBacktrackingMazeSolver::RightHandRuleBacktrackingMazeSolver()
    : Micromouse("rhrb_maze_solver") {}

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
    logger->logMessage("Step " + std::to_string(step) + ": Micromouse made a decision to turn " + direction);
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