#ifndef LIDARSENSOR_H
#define LIDARSENSOR_H

#include "Sensor.h"

class LidarSensor : public Sensor {
public:
    LidarSensor(std::shared_ptr<Maze> maze, std::shared_ptr<Micromouse> micromouse);
    std::vector<std::pair<int, int>> getSensorData() const override;
};

#endif // LIDARSENSOR_H
