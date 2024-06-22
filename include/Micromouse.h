#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include <memory>
#include <vector>
#include <string>

// Forward declaration of Sensor class
class Sensor;
// Circular Inclusion Issue
// When Micromouse.h includes Sensor.h and Sensor.h includes Micromouse.h, the compiler gets confused about the order of declarations and definitions, leading to the error you're seeing.


class Micromouse : public std::enable_shared_from_this<Micromouse> {
public:
    Micromouse(std::shared_ptr<Maze> maze);
    virtual ~Micromouse() = default;

    virtual void initialize() = 0;
    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);
    void move();
    void readSensors();

    // void logMovement(int x, int y);
    // void saveRouteToFile(const std::string& filename) const;

protected:
    int posX, posY;
    std::string direction;
    std::shared_ptr<Maze> maze;
    std::shared_ptr<Sensor> sensor;
    std::vector<std::pair<int, int>> sensorData;
    // std::vector<std::pair<int, int>> route; // to store the route taken
};



class RightHandRuleMazeSolver : public Micromouse {
public:
    RightHandRuleMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

class BacktrackingMazeSolver : public Micromouse {
public:
    BacktrackingMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

class LaserBacktrackingMazeSolver : public Micromouse {
public:
    LaserBacktrackingMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

class LidarBacktrackingMazeSolver : public Micromouse {
public:
    LidarBacktrackingMazeSolver(std::shared_ptr<Maze> maze);
    
    void initialize() override;
    void makeDecision() override;
};

#endif // MICROMOUSE_H
