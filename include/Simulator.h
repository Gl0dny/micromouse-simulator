#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Micromouse.h"
#include "Maze.h"
#include "Logger.h"
#include <memory>
#include <chrono>
#include <atomic>

class Simulator {
public:
    Simulator(std::shared_ptr<Micromouse> micromouse, Maze* maze);

    void run();
    void start();
    void pause();
    void reset();

private:
    void setRandomStartPosition();
    void displayMazeWithMouse() const;
    bool hasReachedGoal() const;
    void checkAndHandleWallCollision();

    std::shared_ptr<Micromouse> micromouse;
    Maze* maze;
    int startX, startY;
    int steps;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::duration<double> totalSeconds;
    std::atomic<bool> running;
    std::unique_ptr<Logger> logger;
};

#endif // SIMULATOR_H
