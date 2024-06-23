#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include "Maze.h"
#include "Micromouse.h"
#include <atomic>
#include <chrono>

class Simulator {
public:
    Simulator(std::shared_ptr<Micromouse> micromouse, Maze* maze);
    void run();
    void start();
    void stop();

private:
    Maze* maze;
    std::shared_ptr<Micromouse> micromouse;
    int startX, startY;
    int steps;
    std::atomic<bool> isRunning;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    void displayMazeWithMouse() const;
    void setRandomStartPosition();
    bool hasReachedGoal() const;
    void checkAndHandleWallCollision(int previousX, int previousY);
};

#endif // SIMULATOR_H
