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
    // if (direction == "North") {
    //     posY--;
    // } else if (direction == "East") {
    //     posX++;
    // } else if (direction == "South") {
    //     posY++;
    // } else if (direction == "West") {
    //     posX--;
    // }
}

void Micromouse::readSensors() {
    std::cout << "Pozycja przed readSensors : " << posX << ", " << posY << std::endl;
    sensor->getSensorData(posX, posY, knownMaze);
}

void Micromouse::initializeKnownMaze(int width, int height) {
    knownMaze = std::vector<std::vector<int>>(width, std::vector<int>(height, -1));
    // knownMaze[start][] = 0;
}

std::vector<std::vector<int>> Micromouse::getKnownMaze() const {
    return knownMaze;
}

RightHandRuleMazeSolver::RightHandRuleMazeSolver()
    : Micromouse() {}

void RightHandRuleMazeSolver::makeDecision() {
    // Implement the right-hand rule logic
}

BacktrackingMazeSolver::BacktrackingMazeSolver()
    : Micromouse() {}

void BacktrackingMazeSolver::makeDecision() {
    // Implement the backtracking logic
}

LaserBacktrackingMazeSolver::LaserBacktrackingMazeSolver()
    : Micromouse() {}

void LaserBacktrackingMazeSolver::makeDecision() {
    // Implement the laser backtracking logic
}

LidarBacktrackingMazeSolver::LidarBacktrackingMazeSolver()
    : Micromouse() {}

void LidarBacktrackingMazeSolver::makeDecision() {
    // Implement the lidar backtracking logic
}
