#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <map>
#include <string>

class Maze {
public:
    Maze(int width, int height);
    void generateMaze();
    bool isWall(int x, int y) const;
    void displayMaze() const;

private:
    int width;
    int height;
    std::vector<std::vector<int>> mazeGrid;
    std::vector<std::pair<int, int>> directions;
    std::map<std::pair<int, int>, std::string> directionNames;

    void carvePassage(int x, int y);
    void createRandomExit();
    bool isValidExit(int x, int y);
    void ensureFullConnectivity();
    void printMazeWithCurrentPosition(int cx, int cy) const;
};

#endif // MAZE_H
