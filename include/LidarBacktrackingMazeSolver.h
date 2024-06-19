#ifndef LIDARBACKTRACKINGMAZESOLVER_H
#define LIDARBACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "LidarSensor.h"
#include <stack>

class LidarBacktrackingMazeSolver : public Micromouse {
public:
    LidarBacktrackingMazeSolver(int startX, int startY, std::shared_ptr<Maze> maze);
    void updateSensors() override;
    void makeDecision() override;

private:
    std::unique_ptr<LidarSensor> lidarSensor;
    std::stack<std::pair<int, int>> pathStack;
};

#endif // LIDARBACKTRACKINGMAZESOLVER_H
