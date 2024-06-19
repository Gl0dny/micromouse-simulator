#include "LidarBacktrackingMazeSolver.h"

LidarBacktrackingMazeSolver::LidarBacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
    sensor = std::make_shared<LidarSensor>(maze, shared_from_this());
}

void LidarBacktrackingMazeSolver::makeDecision() {
    // Implement the lidar backtracking logic
}
