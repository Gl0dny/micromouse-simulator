#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include "Maze.h"

template <typename T>
class Sensor {
public:
    Sensor(std::shared_ptr<Maze> maze, int posX, int posY);
    virtual ~Sensor() = default;
    T getReading(int direction) const;
    virtual void updateReadings(int posX, int posY) = 0;

protected:
    std::shared_ptr<Maze> maze;
    std::vector<T> data;
    int posX, posY;
};

template <typename T>
Sensor<T>::Sensor(std::shared_ptr<Maze> maze, int posX, int posY)
    : maze(maze), posX(posX), posY(posY), data(4, T()) {}

template <typename T>
T Sensor<T>::getReading(int direction) const {
    return data[direction];
}

#endif // SENSOR_H
