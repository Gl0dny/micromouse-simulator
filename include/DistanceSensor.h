#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include "Sensor.h"

class DistanceSensor : public Sensor<bool> {
public:
    DistanceSensor(std::shared_ptr<Maze> maze, int posX, int posY);
    void updateReadings(int posX, int posY) override;
};

#endif // DISTANCESENSOR_H
