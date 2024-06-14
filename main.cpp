#include <iostream>
#include "Maze.h"

int main() {
    int width = 11;  // Szerokość labiryntu
    int height = 11; // Wysokość labiryntu

    Maze maze(width, height);
    maze.generateMaze();
    maze.displayMaze();

    return 0;
}
