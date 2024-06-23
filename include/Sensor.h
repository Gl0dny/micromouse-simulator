#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <utility>
#include "Maze.h"
#include "Logger.h"

class Sensor {
public:
    Sensor(Maze* maze, const std::string& name);
    virtual void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const = 0;

protected:
    Maze* maze;
    std::map<std::pair<int, int>, std::string> directionNames;
    std::unique_ptr<Logger> logger;
    int steps;
};

class DistanceSensor : public Sensor {
public:
    DistanceSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

class LaserSensor : public Sensor {
public:
    LaserSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

class LidarSensor : public Sensor {
public:
    LidarSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

#endif // SENSOR_H
