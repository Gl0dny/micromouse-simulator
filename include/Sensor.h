#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"
#include "Micromouse.h"

class Sensor {
public:
    Sensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse);
    virtual std::vector<std::pair<int, int>> getSensorData() const = 0;

protected:
    std::shared_ptr<Maze> maze;
    std::shared_ptr<Micromouse> micromouse;
};

#endif // SENSOR_H
