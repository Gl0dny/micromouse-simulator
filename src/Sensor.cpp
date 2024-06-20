#include "Sensor.h"

Sensor::Sensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse)
    : maze(maze), micromouse(micromouse) {}
