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
    Sensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    virtual std::vector<std::pair<int, int>> getSensorData() const = 0;

protected:
    std::shared_ptr<Maze> maze;

/*
Potential Circular Dependency:
The Sensor class holds a std::shared_ptr<Micromouse>, which can cause a circular dependency issue when combined with shared_from_this().

Pass weak_ptr to Sensor:
Instead of storing a std::shared_ptr<Micromouse> in the Sensor class, store a std::weak_ptr<Micromouse>. This breaks the circular dependency and avoids potential dangling pointers
*/
    std::weak_ptr<Micromouse> micromouse;
};

class DistanceSensor : public Sensor {
public:
    DistanceSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

class LaserSensor : public Sensor {
public:
    LaserSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

class LidarSensor : public Sensor {
public:
    LidarSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

#endif // SENSOR_H
