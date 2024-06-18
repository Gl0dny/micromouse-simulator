#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include <memory>
#include <vector>
#include "Maze.h"

class Micromouse {
public:
    Micromouse();
    virtual ~Micromouse() = default;

    void move();
    virtual void updateSensors() = 0;
    virtual void makeDecision() = 0;
    bool hasReachedGoal() const;
    void reset();

    int getPosX() const;
    int getPosY() const;
    void setPosition(int startX, int startY);
    void setStartingPosition(int startX, int startY);

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    int startX, startY;
    int direction; // 0 - North, 1 - East, 2 - South, 3 - West
    std::vector<std::pair<int, int>> route; // to store the route taken

};

#endif // MICROMOUSE_H
