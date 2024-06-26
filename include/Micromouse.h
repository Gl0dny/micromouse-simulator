#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Maze.h"
#include "Sensor.h"
#include "Logger.h"
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <utility>

class Micromouse {
public:
    Micromouse(const std::string& logFileName);
    virtual ~Micromouse() = default;

    void setSensor(std::shared_ptr<Sensor> sensor);
    virtual void makeDecision() = 0;

    int getPosX() const;
    int getPosY() const;
    void setPosition(int x, int y);
    void move();
    void readSensors();
    int getStep() const;

    std::vector<std::vector<int>> getKnownMaze() const;
    void initializeKnownMaze(int width, int height);
    
    void reset();

protected:
    int posX, posY;
    std::string direction;
    std::shared_ptr<Sensor> sensor;
    std::vector<std::vector<int>> knownMaze;
    std::unique_ptr<Logger> logger;
    const std::map<std::string, std::pair<int, int>> directions = {
        {"North", {0, 1}}, {"East", {1, 0}}, {"South", {0, -1}}, {"West", {-1, 0}}
    };
    const std::map<std::string, std::string> rightTurns = {
        {"North", "East"}, {"East", "South"}, {"South", "West"}, {"West", "North"}
    };
    const std::map<std::string, std::string> leftTurns = {
        {"North", "West"}, {"West", "South"}, {"South", "East"}, {"East", "North"}
    };
    int step;
};

class RightHandRuleBacktrackingMazeSolver : public Micromouse {
public:
    RightHandRuleBacktrackingMazeSolver();
    void makeDecision() override;
private:
    void followRightHandRule();
};

class CornerDetectionMazeSolver : public Micromouse {
public:
    CornerDetectionMazeSolver();
    void makeDecision() override;

private:
    void followLeftHandRule();
    std::string isCorner(int x, int y);
    // void updateCorners();
    // void assumeCorners();
    void prioritizeOuterWalls();

    // bool cornersAssumed;
    bool confirmedMazeSize;
    // std::pair<int, int> topLeft;
    // std::pair<int, int> topRight;
    // std::pair<int, int> bottomLeft;
    // std::pair<int, int> bottomRight;
};


class TeleportingUndecidedMazeSolver : public Micromouse {
public:
    TeleportingUndecidedMazeSolver();
    void makeDecision() override;

private:
    std::map<std::pair<int, int>, int> visited; // Tracks visited cells
    std::map<std::pair<int, int>, std::set<std::string>> triedDirections; // Tracks tried directions from each cell
    std::stack<std::pair<int, int>> backtrackStack; // Stack for backtracking

    bool hasUntriedDirection(int x, int y);
    std::string getNextDirection(int x, int y);
};

template <typename SolverType, typename SensorType>
std::shared_ptr<Micromouse> createMicromouse(Maze* maze) {
    auto micromouse = std::make_shared<SolverType>();
    auto sensor = std::make_shared<SensorType>(maze);
    micromouse->initializeKnownMaze(maze->getWidth(), maze->getHeight());
    micromouse->setSensor(sensor);
    return micromouse;
}

std::shared_ptr<Micromouse> chooseMicromouse(Maze* maze);

#endif // MICROMOUSE_H
