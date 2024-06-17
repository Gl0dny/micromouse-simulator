#include "Maze.h"
#include "Utils.h"
#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include <memory>

// Constructor
Maze::Maze(int width, int height, const std::string& logFileName)
    : width(width), height(height), mazeGrid(width, std::vector<int>(height, 1)), logger(std::make_unique<Logger>(logFileName)) {
    directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    directionNames = {{{0, -1}, "North"}, {{0, 1}, "South"}, {{-1, 0}, "West"}, {{1, 0}, "East"}};

    logger->enableFileOutput();
    logger->clearLogFile();
    logger->logMessage("Maze initialized with all walls.");
}

// Destructor
Maze::~Maze() {
    logger->disableFileOutput();
}

// Function to generate the maze
Maze& Maze::generateMaze() {
    logger->logMessage("Starting maze generation.");
    
    // Generating the internal maze
    carvePassage(1, 1);

    // Creating one exit
    createRandomExit();

    // Ensuring full connectivity
    // ensureFullConnectivity();

    logger->logMessage("Maze generation completed.");

    return *this;
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
            logger->logMessage("Created exit at (" + std::to_string(exitX) + ", " + std::to_string(exitY) + ").");
            exitCreated = true;
        }
    }

    if (!exitCreated) {
        logger->logMessage("Failed to create a valid exit.");
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
    logger->logMessage("Carving passage at (" + std::to_string(x) + ", " + std::to_string(y) + ").");

    // Print maze with current position
    printMazeWithCurrentPosition(x, y);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx * 2;
        int ny = y + dy * 2;

        std::string directionName = directionNames[{dx, dy}];
        logger->logMessage("Trying direction " + directionName + " to (" + std::to_string(nx) + ", " + std::to_string(ny) + ").");

        if (nx >= 1 && nx < width-1 && ny >= 1 && ny < height-1 && mazeGrid[nx][ny] == 1) {
            logger->logMessage("Direction " + directionName + " is valid, moving to (" + std::to_string(nx) + ", " + std::to_string(ny) + ").");
            mazeGrid[x + dx][y + dy] = 0;
            carvePassage(nx, ny);
        } else {
            logger->logMessage("Direction " + directionName + " is invalid or already visited.");
        }
    }
    
    logger->logMessage("Returning from carving at (" + std::to_string(x) + ", " + std::to_string(y) + ").");
}

// Function to print the maze with the current position of the algorithm
void Maze::printMazeWithCurrentPosition(int cx, int cy) const {
    logger->logMessage("Displaying maze with current position:");

    // Log each row of the maze
    for (int y = 0; y < height; ++y) {
        std::string rowString;
        for (int x = 0; x < width; ++x) {
            if (x == cx && y == cy) {
                rowString += "C "; // Current position
            } else {
                rowString += (mazeGrid[x][y] ? '#' : ' ');
                rowString += ' ';
            }
        }
        logger->logMessage(rowString, false);
    }
}

// // Function to ensure full connectivity of the maze
// void Maze::ensureFullConnectivity() {
//     for (int x = 1; x < width - 1; x += 2) {
//         for (int y = 1; y < height - 1; y += 2) {
//             if (mazeGrid[x][y] == 1) {
//                 carvePassage(x, y);
//             }
//         }
//     }
// }

// Function to check if a cell is a wall
bool Maze::isWall(int x, int y) const {
    return mazeGrid[x][y] == 1;
}

// Function to display the maze
void Maze::displayMaze() const {
    logger->logMessage("Displaying maze:");

    // Log each row of the maze
    for (const auto& row : mazeGrid) {
        std::string rowString;
        for (const auto& cell : row) {
            rowString += (cell ? '#' : ' ');
            rowString += ' ';
        }
        logger->logMessage(rowString, false);
    }
}

Maze& Maze::setLogger(const std::string& log_file, bool toFileOnly /* = true */) {
    logger.reset(new Logger(log_file));
    logger->enableFileOutput(toFileOnly);
    return *this;
}