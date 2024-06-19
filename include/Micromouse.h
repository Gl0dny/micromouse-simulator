#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include <memory>
#include <vector>
#include <string>


class Micromouse {
public:
    Micromouse();
    virtual ~Micromouse() = default;

    virtual void readSensors() = 0;
    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);
    void move();

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    std::string direction;
    // std::vector<std::pair<int, int>> route; // to store the route taken
};

#endif // MICROMOUSE_H
