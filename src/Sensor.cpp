#include "Sensor.h"
#include <iostream>

Sensor::Sensor(std::shared_ptr<Maze> maze)
    : maze(maze) {
    directionNames = {
        {{-1, 0}, "West"},
        {{1, 0}, "East"},
        {{0, -1}, "South"},
        {{0, 1}, "North"},
        {{-1, -1}, "South-West"},
        {{1, -1}, "South-East"},
        {{-1, 1}, "North-West"},
        {{1, 1}, "North-East"}
    };
}

DistanceSensor::DistanceSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void DistanceSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;
    // Only use the four basic directions
    for (const auto& [coordinates, direction] : directionNames) {
        if (direction == "West" || direction == "East" || direction == "South" || direction == "North") {
            int nx = x + coordinates.first;
            int ny = y + coordinates.second;

            if (nx >= 0 && ny >= 0 && nx < knownMaze.size() && ny < knownMaze[0].size()) {
                if (maze->isWall(nx, ny)) {
                    knownMaze[nx][ny] = 1;
                    std::cout << "Wall detected to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
                } else {
                    knownMaze[nx][ny] = 0;
                    std::cout << "No wall detected to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
                }
            } else {
                std::cout << "Out of bounds to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
            }
        }
    }
}

LaserSensor::LaserSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void LaserSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;
    // Only use the four basic directions
    for (const auto& [dir, direction] : directionNames) {
        if (direction == "West" || direction == "East" || direction == "South" || direction == "North") {
            int nx = x;
            int ny = y;
            bool outOfBounds = false;
            while (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight() && !maze->isWall(nx + dir.first, ny + dir.second)) {
                nx += dir.first;
                ny += dir.second;
                knownMaze[nx][ny] = 0;
                std::cout << "Laser detected no wall to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
            }
            if (nx < 0 || ny < 0 || nx >= maze->getWidth() || ny >= maze->getHeight()) {
                outOfBounds = true;
                std::cout << "Out of bounds to the " << direction << " at (" << nx + dir.first << ", " << ny + dir.second << ")" << std::endl;
            }
            if (!outOfBounds && maze->isWall(nx + dir.first, ny + dir.second)) {
                knownMaze[nx + dir.first][ny + dir.second] = 1;
                std::cout << "Laser detected wall to the " << direction << " at (" << nx + dir.first << ", " << ny + dir.second << ")" << std::endl;
            }
        }
    }
}

LidarSensor::LidarSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void LidarSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            if (dx == 0 && dy == 0) continue; // Skip the current position
            
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight()) {
                if (maze->isWall(nx, ny)) {
                    knownMaze[nx][ny] = 1;
                    std::cout << "Lidar detected wall at (" << nx << ", " << ny << ")";
                } else {
                    knownMaze[nx][ny] = 0;
                    std::cout << "Lidar detected no wall at (" << nx << ", " << ny << ")";
                }

                std::string direction;
                if (dx == 0 && dy == 0) {
                    direction = "Current position";
                } else if (dx == 0) {
                    direction = (dy > 0) ? "North" : "South";
                } else if (dy == 0) {
                    direction = (dx > 0) ? "East" : "West";
                } else if (dx > 0 && dy > 0) {
                    direction = "North-East";
                } else if (dx > 0 && dy < 0) {
                    direction = "South-East";
                } else if (dx < 0 && dy > 0) {
                    direction = "North-West";
                } else if (dx < 0 && dy < 0) {
                    direction = "South-West";
                }
                std::cout << " to the " << direction << std::endl;
            } else {
                std::cout << "Out of bounds at (" << nx << ", " << ny << ")";
                std::string direction;
                if (dx == 0 && dy == 0) {
                    direction = "Current position";
                } else if (dx == 0) {
                    direction = (dy > 0) ? "North" : "South";
                } else if (dy == 0) {
                    direction = (dx > 0) ? "East" : "West";
                } else if (dx > 0 && dy > 0) {
                    direction = "North-East";
                } else if (dx > 0 && dy < 0) {
                    direction = "South-East";
                } else if (dx < 0 && dy > 0) {
                    direction = "North-West";
                } else if (dx < 0 && dy < 0) {
                    direction = "South-West";
                }
                std::cout << " to the " << direction << std::endl;
            }
        }
    }
}
