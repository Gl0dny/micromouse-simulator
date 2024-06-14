#include <iostream>
#include "Maze.h"

int main() {
    int width = 21;  // Szerokość labiryntu
    int height = 21; // Wysokość labiryntu

    Maze maze(width, height);
    maze.generateMaze();
    maze.displayMaze();

    return 0;
}
