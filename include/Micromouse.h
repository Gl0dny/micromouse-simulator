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

    int getPosX() const;
    int getPosY() const;
    void setPosition(int startX, int startY);
    void setStartingPosition(int startX, int startY);

    virtual void updateSensors() = 0;
    virtual void makeDecision() = 0;
    void move();
    bool hasReachedGoal() const;
    void reset();

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    int startX, startY;
    int direction; // 0 - North, 1 - East, 2 - South, 3 - West
    // std::unique_ptr<Sensor<bool>> distanceSensor;
    // std::unique_ptr<Sensor<int>> advancedLaserSensor;
    // std::unique_ptr<Sensor<bool>> lidarSensor;
    std::vector<std::pair<int, int>> route; // to store the route taken
};

#endif // MICROMOUSE_H
