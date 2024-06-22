#include "Sensor.h"

Sensor::Sensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : maze(maze), micromouse(micromouse) {}

DistanceSensor::DistanceSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> DistanceSensor::getSensorData() const {
    // std::vector<std::pair<int, int>> data;
    std::vector<std::pair<int, int>> sensorData;

    if (auto micromouseShared = micromouse.lock()) { // Lock the weak_ptr to get a shared_ptr
        int x = micromouseShared->getPosX();
        int y = micromouseShared->getPosY();
        std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

        for (const auto& dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (maze->isWall(nx, ny)) {
                sensorData.push_back(dir);
            }
        }
        return sensorData;
    }
    //     // Check for walls in four directions: up, down, left, right
    //     if (maze->isWall(x, y - 1)) data.emplace_back(x, y - 1); // Up
    //     if (maze->isWall(x, y + 1)) data.emplace_back(x, y + 1); // Down
    //     if (maze->isWall(x - 1, y)) data.emplace_back(x - 1, y); // Left
    //     if (maze->isWall(x + 1, y)) data.emplace_back(x + 1, y); // Right
    // }
    // return data;
}

LaserSensor::LaserSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> LaserSensor::getSensorData() const {
    // std::vector<std::pair<int, int>> data;
    std::vector<std::pair<int, int>> sensorData;
    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    if (auto micromouseShared = micromouse.lock()) { // Lock the weak_ptr to get a shared_ptr
        int x = micromouseShared->getPosX();
        int y = micromouseShared->getPosY();

    for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        while (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight() && !maze->isWall(nx, ny)) {
            nx += dir.first;
            ny += dir.second;
        }
        sensorData.push_back({nx, ny});
    }
    return sensorData;
    }
    //     // Check for walls in four directions and add all positions up to the wall
    //     for (int i = 1; !maze->isWall(x, y - i); ++i) data.emplace_back(x, y - i); // Up
    //     for (int i = 1; !maze->isWall(x, y + i); ++i) data.emplace_back(x, y + i); // Down
    //     for (int i = 1; !maze->isWall(x - i, y); ++i) data.emplace_back(x - i, y); // Left
    //     for (int i = 1; !maze->isWall(x + i, y); ++i) data.emplace_back(x + i, y); // Right
    // }

    // return data;
}

LidarSensor::LidarSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> LidarSensor::getSensorData() const {
    // std::vector<std::pair<int, int>> data;
    std::vector<std::pair<int, int>> sensorData;
    std::vector<std::pair<int, int>> directions = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    if (auto micromouseShared = micromouse.lock()) { // Lock the weak_ptr to get a shared_ptr
        int x = micromouseShared->getPosX();
        int y = micromouseShared->getPosY();

        for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        sensorData.push_back({nx, ny});
    }
    return sensorData;
    }
    //     // Check for walls in nine directions
    //     for (int dx = -1; dx <= 1; ++dx) {
    //         for (int dy = -1; dy <= 1; ++dy) {
    //             if (maze->isWall(x + dx, y + dy)) {
    //                 data.emplace_back(x + dx, y + dy);
    //             }
    //         }
    //     }
    // }

    // return data;
}