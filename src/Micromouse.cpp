#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse(std::shared_ptr<Maze> maze)
    : maze(maze), posX(1), posY(1), direction("North") {}

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
        posY--;
    } else if (direction == "East") {
        posX++;
    } else if (direction == "South") {
        posY++;
    } else if (direction == "West") {
        posX--;
    }
}

// void Micromouse::logMovement(int newX, int newY) {
//     route.emplace_back(newX, newY);
// }

// void Micromouse::saveRouteToFile(const std::string& filename) const {
//     std::ofstream outFile(filename);
//     if (outFile.is_open()) {
//         for (const auto& position : route) {
//             outFile << position.first << "," << position.second << std::endl;
//         }
//     }
//     outFile.close();
// }

void Micromouse::readSensors() {
    sensorData = sensor->getSensorData();
    // Additional processing of sensor data if needed
}




RightHandRuleMazeSolver::RightHandRuleMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
/* 
Micromouse Constructor and shared_from_this() Usage:
The Micromouse class inherits from std::enable_shared_from_this<Micromouse>, which allows an object to create a std::shared_ptr instance to itself.

Potential Issue: Calling shared_from_this() in Constructor

When calling shared_from_this() inside the constructor of a class that inherits from std::enable_shared_from_this, it is crucial that the object is already owned by a std::shared_ptr. This is because shared_from_this() relies on the object being managed by a shared_ptr.
In the current setup, the constructor of RightHandRuleMazeSolver calls shared_from_this() to pass to the DistanceSensor. If this happens too early, shared_from_this() will throw a std::bad_weak_ptr exception because the shared_ptr might not be fully established yet.

Solution: Delayed Initialization
One way to handle this is to avoid calling shared_from_this() directly in the constructor and use a separate initialization function. This function will be called after the shared_ptr has been established.
*/
// sensor = std::make_shared<DistanceSensor>(maze, shared_from_this());
}

void RightHandRuleMazeSolver::initialize() {
    sensor = std::make_shared<DistanceSensor>(maze, shared_from_this());
}

void RightHandRuleMazeSolver::makeDecision() {
    // Implement the right-hand rule logic
}



BacktrackingMazeSolver::BacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {}

void BacktrackingMazeSolver::initialize() {
    sensor = std::make_shared<DistanceSensor>(maze, shared_from_this());
}

void BacktrackingMazeSolver::makeDecision() {
    // Implement the backtracking logic
}



LaserBacktrackingMazeSolver::LaserBacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
}

void LaserBacktrackingMazeSolver::initialize() {
    sensor = std::make_shared<LaserSensor>(maze, shared_from_this());
}

void LaserBacktrackingMazeSolver::makeDecision() {
    // Implement the laser backtracking logic
}


LidarBacktrackingMazeSolver::LidarBacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
}

void LidarBacktrackingMazeSolver::initialize() {
    sensor = std::make_shared<LidarSensor>(maze, shared_from_this());
}

void LidarBacktrackingMazeSolver::makeDecision() {
    // Implement the lidar backtracking logic
}
