#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include <memory>
#include <vector>


class Micromouse {
public:
    Micromouse();
    virtual ~Micromouse() = default;

    virtual void updateSensors() = 0;
    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);

    void move();
    bool hasReachedGoal() const;

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    int direction; // 0 - North, 1 - East, 2 - South, 3 - West
    // std::unique_ptr<Sensor<bool>> distanceSensor;
    // std::unique_ptr<Sensor<int>> advancedLaserSensor;
    // std::unique_ptr<Sensor<bool>> lidarSensor;
    std::vector<std::pair<int, int>> route; // to store the route taken
};

#endif // MICROMOUSE_H
