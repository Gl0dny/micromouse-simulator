#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Robot.h"
#include "Maze.h"

class Simulator {
public:
    Simulator(Robot* robot);
    void runSimulation();
    void resetSimulation();

private:
    Robot* robot;
    Maze* maze;
};

#endif // SIMULATOR_H
