#include "BacktrackingMazeSolver.h"

BacktrackingMazeSolver::BacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
    sensor = std::make_shared<DistanceSensor>(maze, shared_from_this());
}

void BacktrackingMazeSolver::makeDecision() {
    // Implement the backtracking logic
}
