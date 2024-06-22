#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include <memory>
#include <vector>
#include <string>

class Micromouse {
public:
    Micromouse();
    virtual ~Micromouse() = default;

    void setSensor(std::shared_ptr<Sensor> sensor);
    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);
    void move();
    void readSensors();

    std::vector<std::vector<int>> getKnownMaze() const;
    void initializeKnownMaze(int width, int height);

protected:
    int posX, posY;
    std::string direction;
    std::shared_ptr<Sensor> sensor;
    std::vector<std::vector<int>> knownMaze;
};

class RightHandRuleMazeSolver : public Micromouse {
public:
    RightHandRuleMazeSolver();
    void makeDecision() override;
};

class BacktrackingMazeSolver : public Micromouse {
public:
    BacktrackingMazeSolver();
    void makeDecision() override;
};

class LaserBacktrackingMazeSolver : public Micromouse {
public:
    LaserBacktrackingMazeSolver();
    void makeDecision() override;
};

class LidarBacktrackingMazeSolver : public Micromouse {
public:
    LidarBacktrackingMazeSolver();
    void makeDecision() override;
};

template <typename SolverType, typename SensorType>
std::shared_ptr<Micromouse> createMicromouse(std::shared_ptr<Maze> maze) {
    auto micromouse = std::make_shared<SolverType>();
    auto sensor = std::make_shared<SensorType>(maze);
    micromouse->initializeKnownMaze(maze->getWidth(), maze->getHeight());
    micromouse->setSensor(sensor);
    return micromouse;
}

#endif // MICROMOUSE_H
