#ifndef MAZE_H
#define MAZE_H

#include "Logger.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

class Maze {
public:
    Maze(int width, int height);
    Maze& generateMaze();
    bool isWall(int x, int y) const;
    void displayMaze() const;
    Maze& setLogger(const std::string& log_file, bool toFileOnly= true);

    ~Maze();

private:
    int width;
    int height;
    std::vector<std::vector<int>> mazeGrid;
    std::vector<std::pair<int, int>> directions;
    std::map<std::pair<int, int>, std::string> directionNames;
    std::string maze_log_file = "./logs/maze.log";
    std::unique_ptr<Logger> logger;

    void carvePassage(int x, int y);
    void createRandomExit();
    bool isValidExit(int x, int y);
    // void ensureFullConnectivity();
    void printMazeWithCurrentPosition(int cx, int cy) const;
};

#endif // MAZE_H
