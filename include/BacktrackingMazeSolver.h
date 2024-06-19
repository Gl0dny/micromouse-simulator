#ifndef BACKTRACKINGMAZESOLVER_H
#define BACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "DistanceSensor.h"
#include <stack>

class BacktrackingMazeSolver : public Micromouse {
public:
    BacktrackingMazeSolver(int startX, int startY, std::shared_ptr<Maze> maze);
    void updateSensors() override;
    void makeDecision() override;

private:
    std::unique_ptr<DistanceSensor> distanceSensor;
    std::stack<std::pair<int, int>> pathStack;
};

#endif // BACKTRACKINGMAZESOLVER_H
