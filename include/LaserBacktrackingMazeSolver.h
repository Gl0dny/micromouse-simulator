#ifndef LASERBACKTRACKINGMAZESOLVER_H
#define LASERBACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "LaserSensor.h"

class LaserBacktrackingMazeSolver : public Micromouse {
public:
    LaserBacktrackingMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

#endif // LASERBACKTRACKINGMAZESOLVER_H
