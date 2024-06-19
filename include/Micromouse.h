#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include <memory>
#include <vector>
#include <string>


class Micromouse : public std::enable_shared_from_this<Micromouse> {
    
public:
    Micromouse(std::shared_ptr<Maze> maze);
    
    virtual ~Micromouse() = default;

    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);
    void move();
    void readSensors();

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    std::string direction;
    std::shared_ptr<Maze> maze;
    std::shared_ptr<Sensor> sensor;
    std::vector<std::pair<int, int>> sensorData;
    // std::vector<std::pair<int, int>> route; // to store the route taken
};

#endif // MICROMOUSE_H
