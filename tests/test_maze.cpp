#include "Maze.h"
#include <cassert>
#include <iostream>

void test_maze_initialization() {
    Maze maze(10, 10);
    assert(maze.getWidth() == 10);
    assert(maze.getHeight() == 10);
    std::cout << "test_maze_initialization passed." << std::endl;
}

void test_maze_walls() {
    Maze maze(10, 10);
    maze.generateMaze();
    
    for (int y = 0; y < maze.getHeight(); ++y) {
        for (int x = 0; x < maze.getWidth(); ++x) {
            bool isWall = maze.isWall(x, y);
            std::cout << "Position (" << x << ", " << y << ") is "
                      << (isWall ? "a wall." : "not a wall.") << std::endl;
        }
    }
    std::cout << "test_maze_walls passed." << std::endl;
}

int main() {
    test_maze_initialization();
    test_maze_walls();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
