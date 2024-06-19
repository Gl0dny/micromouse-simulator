#ifndef LIDARBACKTRACKINGMAZESOLVER_H
#define LIDARBACKTRACKINGMAZESOLVER_H

#include "Micromouse.h"
#include "LidarSensor.h"

class LidarBacktrackingMazeSolver : public Micromouse {
public:
    LidarBacktrackingMazeSolver(std::shared_ptr<Maze> maze);

    void makeDecision() override;
};

#endif // LIDARBACKTRACKINGMAZESOLVER_H
