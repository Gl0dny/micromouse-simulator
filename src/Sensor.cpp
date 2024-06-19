#include "Sensor.h"

Sensor::Sensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse)
    : maze(maze), micromouse(micromouse) {}
