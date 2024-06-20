#include "LaserBacktrackingMazeSolver.h"

LaserBacktrackingMazeSolver::LaserBacktrackingMazeSolver(std::shared_ptr<Maze> maze)
    : Micromouse(maze) {
}

void LaserBacktrackingMazeSolver::initialize() {
    sensor = std::make_shared<LaserSensor>(maze, shared_from_this());
}

void LaserBacktrackingMazeSolver::makeDecision() {
    // Implement the laser backtracking logic
}
