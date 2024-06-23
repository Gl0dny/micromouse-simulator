#include "Sensor.h"
#include <iostream>

Sensor::Sensor(Maze* maze, const std::string& name)
    : maze(maze), logger(std::make_unique<Logger>("logs/" + name + ".log")) {
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
    logger->enableFileOutput();
}

DistanceSensor::DistanceSensor(Maze* maze)
    : Sensor(maze, "distance_sensor") {}

void DistanceSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;
    for (const auto& [coordinates, direction] : directionNames) {
        if (direction == "West" || direction == "East" || direction == "South" || direction == "North") {
            int nx = x + coordinates.first;
            int ny = y + coordinates.second;

            if (nx >= 0 && ny >= 0 && nx < knownMaze.size() && ny < knownMaze[0].size()) {
                if (maze->isWall(nx, ny)) {
                    knownMaze[nx][ny] = 1;
                    logger->logMessage("Wall detected to the " + direction + " at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
                } else {
                    knownMaze[nx][ny] = 0;
                    logger->logMessage("No wall detected to the " + direction + " at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
                }
            } else {
                logger->logMessage("Out of bounds to the " + direction + " at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
            }
        }
    }
}

LaserSensor::LaserSensor(Maze* maze)
    : Sensor(maze, "laser_sensor") {}

void LaserSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;
    for (const auto& [dir, direction] : directionNames) {
        if (direction == "West" || direction == "East" || direction == "South" || direction == "North") {
            int nx = x;
            int ny = y;
            bool outOfBounds = false;
            while (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight() && !maze->isWall(nx + dir.first, ny + dir.second)) {
                nx += dir.first;
                ny += dir.second;
                knownMaze[nx][ny] = 0;
                logger->logMessage("Laser detected no wall to the " + direction + " at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
            }
            if (nx < 0 || ny < 0 || nx >= maze->getWidth() || ny >= maze->getHeight()) {
                outOfBounds = true;
                logger->logMessage("Out of bounds to the " + direction + " at (" + std::to_string(nx + dir.first) + ", " + std::to_string(ny + dir.second) + ")");
            }
            if (!outOfBounds && maze->isWall(nx + dir.first, ny + dir.second)) {
                knownMaze[nx + dir.first][ny + dir.second] = 1;
                logger->logMessage("Laser detected wall to the " + direction + " at (" + std::to_string(nx + dir.first) + ", " + std::to_string(ny + dir.second) + ")");
            }
        }
    }
}

LidarSensor::LidarSensor(Maze* maze)
    : Sensor(maze, "lidar_sensor") {}

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
                    logger->logMessage("Lidar detected wall at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
                } else {
                    knownMaze[nx][ny] = 0;
                    logger->logMessage("Lidar detected no wall at (" + std::to_string(nx) + ", " + std::to_string(ny) + ")");
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
                logger->logMessage(" to the " + direction);
            } else {
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
                logger->logMessage("Out of bounds at (" + std::to_string(nx) + ", " + std::to_string(ny) + ") to the " + direction);
            }
        }
    }
}
