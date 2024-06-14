#include "Maze.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <vector>

// Constructor
Maze::Maze(int width, int height)
    : width(width), height(height), mazeGrid(width, std::vector<int>(height, 1)) {
    directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    directionNames = {{{0, -1}, "North"}, {{0, 1}, "South"}, {{-1, 0}, "West"}, {{1, 0}, "East"}};
    Utils::logMessage("Maze initialized with all walls.");
}

// Function to generate the maze
void Maze::generateMaze() {
    Utils::logMessage("Starting maze generation.");
    
    // Generating the internal maze
    carvePassage(1, 1);

    // Creating one exit
    createRandomExit();

    // Ensuring full connectivity
    // ensureFullConnectivity();

    Utils::logMessage("Maze generation completed.");
}

// Function to create a random exit on the maze border (excluding corners and ensuring no adjacent inner walls)
void Maze::createRandomExit() {
    std::vector<std::pair<int, int>> borderCells;
    for (int i = 1; i < width - 1; ++i) {
        borderCells.push_back({i, 0});        // Top border
        borderCells.push_back({i, height-1}); // Bottom border
    }
    for (int i = 1; i < height - 1; ++i) {
        borderCells.push_back({0, i});        // Left border
        borderCells.push_back({width-1, i});  // Right border
    }

    // Remove corners
    borderCells.erase(std::remove(borderCells.begin(), borderCells.end(), std::make_pair(0, 0)), borderCells.end());
    borderCells.erase(std::remove(borderCells.begin(), borderCells.end(), std::make_pair(0, height-1)), borderCells.end());
    borderCells.erase(std::remove(borderCells.begin(), borderCells.end(), std::make_pair(width-1, 0)), borderCells.end());
    borderCells.erase(std::remove(borderCells.begin(), borderCells.end(), std::make_pair(width-1, height-1)), borderCells.end());

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, borderCells.size() - 1);

    bool exitCreated = false;
    while (!exitCreated && !borderCells.empty()) {
        int idx = dis(g);
        auto [exitX, exitY] = borderCells[idx];
        borderCells.erase(borderCells.begin() + idx);

        if (isValidExit(exitX, exitY)) {
            mazeGrid[exitX][exitY] = 0;
            Utils::logMessage("Created exit at (" + std::to_string(exitX) + ", " + std::to_string(exitY) + ").");
            exitCreated = true;
        }
    }

    if (!exitCreated) {
        Utils::logMessage("Failed to create a valid exit.");
    }
}

// Function to check if the exit is valid (not adjacent to inner walls)
bool Maze::isValidExit(int x, int y) {
    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && mazeGrid[nx][ny] == 1) {
            return false;
        }
    }
    return true;
}

// Function to carve passage at given coordinates
void Maze::carvePassage(int x, int y) {
    mazeGrid[x][y] = 0;
    Utils::logMessage("Carving passage at (" + std::to_string(x) + ", " + std::to_string(y) + ").");

    // Print maze with current position
    printMazeWithCurrentPosition(x, y);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx * 2;
        int ny = y + dy * 2;

        std::string directionName = directionNames[{dx, dy}];
        Utils::logMessage("Trying direction " + directionName + " to (" + std::to_string(nx) + ", " + std::to_string(ny) + ").");

        if (nx >= 1 && nx < width-1 && ny >= 1 && ny < height-1 && mazeGrid[nx][ny] == 1) {
            Utils::logMessage("Direction " + directionName + " is valid, moving to (" + std::to_string(nx) + ", " + std::to_string(ny) + ").");
            mazeGrid[x + dx][y + dy] = 0;
            carvePassage(nx, ny);
        } else {
            Utils::logMessage("Direction " + directionName + " is invalid or already visited.");
        }
    }
    
    Utils::logMessage("Returning from carving at (" + std::to_string(x) + ", " + std::to_string(y) + ").");
}

// Function to print the maze with the current position of the algorithm
void Maze::printMazeWithCurrentPosition(int cx, int cy) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == cx && y == cy) {
                std::cout << "C "; // Current position
            } else {
                std::cout << (mazeGrid[x][y] ? '#' : ' ') << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

// Function to ensure full connectivity of the maze
void Maze::ensureFullConnectivity() {
    for (int x = 1; x < width - 1; x += 2) {
        for (int y = 1; y < height - 1; y += 2) {
            if (mazeGrid[x][y] == 1) {
                carvePassage(x, y);
            }
        }
    }
}

// Function to check if a cell is a wall
bool Maze::isWall(int x, int y) const {
    return mazeGrid[x][y] == 1;
}

// Function to display the maze
void Maze::displayMaze() const {
    Utils::logMessage("Displaying maze:");
    for (const auto& row : mazeGrid) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}
