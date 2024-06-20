#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> DistanceSensor::getSensorData() const {
    std::vector<std::pair<int, int>> data;
    if (auto micromouseShared = micromouse.lock()) { // Lock the weak_ptr to get a shared_ptr
        int x = micromouseShared->getPosX();
        int y = micromouseShared->getPosY();
        // Check for walls in four directions: up, down, left, right
        if (maze->isWall(x, y - 1)) data.emplace_back(x, y - 1); // Up
        if (maze->isWall(x, y + 1)) data.emplace_back(x, y + 1); // Down
        if (maze->isWall(x - 1, y)) data.emplace_back(x - 1, y); // Left
        if (maze->isWall(x + 1, y)) data.emplace_back(x + 1, y); // Right
    }
    return data;
}
