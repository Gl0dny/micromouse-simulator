#ifndef LASERBACKTRACKINGMAZESOLVER_H
#define LASERBACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "LaserSensor.h"
#include <stack>

class LaserBacktrackingMazeSolver : public Micromouse {
public:
    LaserBacktrackingMazeSolver(int startX, int startY, std::shared_ptr<Maze> maze);
    void updateSensors() override;
    void makeDecision() override;

private:
    std::unique_ptr<LaserSensor> laserSensor;
    std::stack<std::pair<int, int>> pathStack;
};

#endif // LASERBACKTRACKINGMAZESOLVER_H
