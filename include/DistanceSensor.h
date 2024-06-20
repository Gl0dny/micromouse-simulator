#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "Sensor.h"

class DistanceSensor : public Sensor {
public:
    DistanceSensor(std::shared_ptr<Maze> maze, std::weak_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

#endif // DISTANCESENSOR_H
