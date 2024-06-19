#ifndef LIDARSENSOR_H
#define LIDARSENSOR_H

#include "Sensor.h"

class LidarSensor : public Sensor<bool> {
public:
    LidarSensor(std::shared_ptr<Maze> maze, int posX, int posY);
    void updateReadings(int posX, int posY) override;
};

#endif // LIDARSENSOR_H
