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
    ~Maze();

    // Returns the single instance of Maze
    static Maze* getInstance();

    // Delete copy constructor and assignment operator to prevent duplicates
    Maze(Maze const &) = delete;
    void operator=(Maze const &) = delete;

    int getWidth() const;
    int getHeight() const;
    void displayMaze() const;
    const std::vector<std::vector<int>> &getMazeGrid() const;
    std::pair<int, int> readExit() const;
    bool isWall(int x, int y) const;

    Maze &setLogger(const std::string &logFile, bool toFileOnly = true);

private:
   // Private constructor to prevent instantiation
    Maze();
   // Static member pointer to hold the instance
    static Maze* instance;
    int width;
    int height;
    std::vector<std::vector<int>> mazeGrid;
    std::pair<int, int> exit;
    std::unique_ptr<Logger> logger;
    std::map<std::pair<int, int>, std::string> directionNames;

    void generateMaze();
    void carvePassage(int x, int y);
    void createRandomExit();
    bool isValidExit(int x, int y);
    void printMazeWithCurrentCarve(int cx, int cy) const;
};

#endif // MAZE_H
