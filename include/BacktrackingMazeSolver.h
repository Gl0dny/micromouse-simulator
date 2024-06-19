#ifndef BACKTRACKINGMAZESOLVER_H
#define BACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "DistanceSensor.h"

class BacktrackingMazeSolver : public Micromouse {
public:
    BacktrackingMazeSolver(std::shared_ptr<Maze> maze);

    void makeDecision() override;
};

#endif // BACKTRACKINGMAZESOLVER_H
