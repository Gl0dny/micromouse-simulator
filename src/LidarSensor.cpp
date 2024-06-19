#include "LidarSensor.h"

LidarSensor::LidarSensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse)
    : Sensor(maze, micromouse) {}

std::vector<std::pair<int, int>> LidarSensor::getSensorData() const {
    std::vector<std::pair<int, int>> data;
    int x = micromouse->getPosX();
    int y = micromouse->getPosY();

    // Check for walls in nine directions
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (maze->isWall(x + dx, y + dy)) {
                data.emplace_back(x + dx, y + dy);
            }
        }
    }

    return data;
}
