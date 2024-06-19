#ifndef LASERSENSOR_H
#define LASERSENSOR_H

#include "Sensor.h"

class LaserSensor : public Sensor<int>
{
public:
    LaserSensor(std::shared_ptr<Maze> maze, int posX, int posY);
    void updateReadings(int posX, int posY) override;
};

#endif // LASERSENSOR_H
