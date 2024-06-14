#include "Maze.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <random>

Maze::Maze(int width, int height)
    : width(width), height(height), mazeGrid(width, std::vector<int>(height, 1)) {
    directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    Utils::logMessage("Maze initialized with all walls.");
}

void Maze::generateMaze() {
    Utils::logMessage("Starting maze generation.");
    
    // Generowanie labiryntu wewnętrznego
    carvePassage(1, 1);

    // Dodanie ścian dookoła
    for (int x = 0; x < width; ++x) {
        mazeGrid[x][0] = 1;
        mazeGrid[x][height-1] = 1;
    }

    for (int y = 0; y < height; ++y) {
        mazeGrid[0][y] = 1;
        mazeGrid[width-1][y] = 1;
    }

    // Tworzenie jednego wyjścia
    mazeGrid[width-2][height-1] = 0;

    Utils::logMessage("Maze generation completed.");
}

void Maze::carvePassage(int x, int y) {
    mazeGrid[x][y] = 0;
    Utils::logMessage("Carving passage at (" + std::to_string(x) + ", " + std::to_string(y) + ").");

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx * 2;
        int ny = y + dy * 2;

        if (nx >= 1 && nx < width-1 && ny >= 1 && ny < height-1 && mazeGrid[nx][ny] == 1) {
            mazeGrid[x + dx][y + dy] = 0;
            // carvePassage(nx, ny);
        }
    }
}

bool Maze::isWall(int x, int y) const {
    return mazeGrid[x][y] == 1;
}

void Maze::displayMaze() const {
    Utils::logMessage("Displaying maze:");
    for (const auto& row : mazeGrid) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}
