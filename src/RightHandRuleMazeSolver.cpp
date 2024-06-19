#include "RightHandRuleMazeSolver.h"

RightHandRuleMazeSolver::RightHandRuleMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
    sensor = std::make_shared<DistanceSensor>(maze, shared_from_this());
}

void RightHandRuleMazeSolver::makeDecision() {
    // Implement the right-hand rule logic
}
