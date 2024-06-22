#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"

class Sensor {
public:
    Sensor(std::shared_ptr<Maze> maze);
    virtual void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const = 0;

protected:
    std::shared_ptr<Maze> maze;
    std::map<std::pair<int, int>, std::string> directionNames;
};

class DistanceSensor : public Sensor {
public:
    DistanceSensor(std::shared_ptr<Maze> maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

class LaserSensor : public Sensor {
public:
    LaserSensor(std::shared_ptr<Maze> maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

class LidarSensor : public Sensor {
public:
    LidarSensor(std::shared_ptr<Maze> maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

#endif // SENSOR_H
