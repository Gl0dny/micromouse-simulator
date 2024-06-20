#include "LidarSensor.h"

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
