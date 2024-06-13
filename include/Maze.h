#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
public:
    Maze(int width, int height);
    void generateMaze();
    bool isWall(int x, int y) const;
    void displayMaze() const;

private:
    int width, height;
    std::vector<std::vector<int>> mazeGrid;
};

#endif // MAZE_H
