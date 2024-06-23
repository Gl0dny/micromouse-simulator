#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include "Maze.h"
#include "Micromouse.h"

class Simulator {
public:
    Simulator(std::shared_ptr<Micromouse> micromouse, Maze* maze);
    void run();

private:
    Maze* maze;
    std::shared_ptr<Micromouse> micromouse;
    int startX, startY;
    void displayMazeWithMouse() const;
    void setRandomStartPosition();
    bool hasReachedGoal() const;
    void checkAndHandleWallCollision(int previousX, int previousY);
};

#endif // SIMULATOR_H
