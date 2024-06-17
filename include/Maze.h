// Maze.h
#ifndef MAZE_H
#define MAZE_H

#include "Logger.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

class Maze {
public:
    Maze(int width, int height, const std::string& logFileName);
    ~Maze();
    Maze& generateMaze();
    void displayMaze() const;
    bool isWall(int x, int y) const;
    Maze& setLogger(const std::string& logFile, bool toFileOnly = true);

private:
    int width;
    int height;
    std::vector<std::vector<int>> mazeGrid;
    std::unique_ptr<Logger> logger;
    std::map<std::pair<int, int>, std::string> directionNames;

    void carvePassage(int x, int y);
    void createRandomExit();
    bool isValidExit(int x, int y);
    void printMazeWithCurrentPosition(int cx, int cy) const;
};

#endif // MAZE_H
