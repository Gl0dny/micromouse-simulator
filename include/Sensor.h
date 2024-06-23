#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"

class Sensor {
public:
    Sensor(Maze* maze);
    virtual void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const = 0;

protected:
    Maze* maze;
    std::map<std::pair<int, int>, std::string> directionNames;
};

class DistanceSensor : public Sensor {
public:
    DistanceSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

class LaserSensor : public Sensor {
public:
    LaserSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

class LidarSensor : public Sensor {
public:
    LidarSensor(Maze* maze);
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const override;
};

#endif // SENSOR_H
