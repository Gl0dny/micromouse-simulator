#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"
#include "Micromouse.h"

// Forward declaration of Micromouse class
class Micromouse;
// Circular Inclusion Issue
// When Micromouse.h includes Sensor.h and Sensor.h includes Micromouse.h, the compiler gets confused about the order of declarations and definitions, leading to the error you're seeing.

class Sensor {
public:
    Sensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse);
    virtual std::vector<std::pair<int, int>> getSensorData() const = 0;

protected:
    std::shared_ptr<Maze> maze;
    std::shared_ptr<Micromouse> micromouse;
};

#endif // SENSOR_H
