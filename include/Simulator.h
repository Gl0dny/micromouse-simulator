#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include "Maze.h"
#include "Micromouse.h"

class Simulator {
public:
    Simulator(std::shared_ptr<Micromouse> mmouse);
    void run();

private:
    std::shared_ptr<Maze> maze;
    std::shared_ptr<Micromouse> micromouse;
    void displayMazeWithMouse() const;
    void setRandomStartPosition();
};

#endif // SIMULATOR_H
