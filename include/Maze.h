#ifndef MAZE_H
#define MAZE_H

#include "Logger.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <utility>

class Maze
{
public:
    Maze(int width, int height, const std::string &logFileName);
    ~Maze();
    Maze &generateMaze();
    void displayMaze() const;
    bool isWall(int x, int y) const;
    Maze &setLogger(const std::string &logFile, bool toFileOnly = true);
    const std::vector<std::vector<int>> &getMazeGrid() const;
    int getWidth() const;
    int getHeight() const;
    std::pair<int, int> readExit() const;
    std::vector<std::vector<int>> mazeGrid;
private:
    int width;
    int height;

    std::unique_ptr<Logger> logger;
    std::map<std::pair<int, int>, std::string> directionNames;

    void carvePassage(int x, int y);
    std::pair<int, int> exit;
    void createRandomExit();
    bool isValidExit(int x, int y);
    void printMazeWithCurrentCarve(int cx, int cy) const;
};

#endif // MAZE_H
