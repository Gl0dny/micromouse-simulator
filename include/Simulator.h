#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include "Maze.h"
#include "Micromouse.h"

class Simulator {
public:
    Simulator(Micromouse& mmouse);
    void run();

private:
    std::shared_ptr<Maze> maze;
    Micromouse& micromouse;
    void displayMazeWithMouse() const;
    void setRandomStartPosition();
};

#endif // SIMULATOR_H
