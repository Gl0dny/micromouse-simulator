#include "LaserSensor.h"

LaserSensor::LaserSensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> LaserSensor::getSensorData() const {
    std::vector<std::pair<int, int>> data;
    int x = micromouse->getPosX();
    int y = micromouse->getPosY();

    // Check for walls in four directions and add all positions up to the wall
    for (int i = 1; !maze->isWall(x, y - i); ++i) data.emplace_back(x, y - i); // Up
    for (int i = 1; !maze->isWall(x, y + i); ++i) data.emplace_back(x, y + i); // Down
    for (int i = 1; !maze->isWall(x - i, y); ++i) data.emplace_back(x - i, y); // Left
    for (int i = 1; !maze->isWall(x + i, y); ++i) data.emplace_back(x + i, y); // Right

    return data;
}
