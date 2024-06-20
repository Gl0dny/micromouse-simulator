#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "Sensor.h"

class LaserSensor : public Sensor {
public:
    LaserSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

#endif // LASERSENSOR_H
