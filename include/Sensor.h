#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"

class Sensor {
public:
    Sensor(std::shared_ptr<Maze> maze);
    virtual std::vector<std::pair<int, int>> getSensorData(int x, int y) const = 0;

protected:
    std::shared_ptr<Maze> maze;
};

class DistanceSensor : public Sensor {
public:
    DistanceSensor(std::shared_ptr<Maze> maze);
    std::vector<std::pair<int, int>> getSensorData(int x, int y) const;
};

class LaserSensor : public Sensor {
public:
    LaserSensor(std::shared_ptr<Maze> maze);
    std::vector<std::pair<int, int>> getSensorData(int x, int y) const;
};

class LidarSensor : public Sensor {
public:
    LidarSensor(std::shared_ptr<Maze> maze);
    std::vector<std::pair<int, int>> getSensorData(int x, int y) const;
};

#endif // SENSOR_H
