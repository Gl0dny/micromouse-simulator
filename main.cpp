#include "Simulator.h"
#include "RightHandRuleMazeSolver.h"
#include "BacktrackingMazeSolver.h"
#include "LaserBacktrackingMazeSolver.h"
#include "LidarBacktrackingMazeSolver.h"
#include <memory>
#include <iostream>
#include <string>

int main() {
    auto main_log_file = "./logs/main.log";
    auto logger = std::make_unique<Logger>(main_log_file);
    int width = 21;
    int height = 21;
    
    // Creating a unique log file name for the maze
    auto maze_log_file = "./logs/maze.log";
    auto maze = std::make_shared<Maze>(width, height, maze_log_file);

    logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze: ");
    maze->generateMaze().displayMaze();
    maze->setLogger(main_log_file, false).displayMaze();

    std::shared_ptr<Micromouse> micromouse;

    // Choose the type of Micromouse
    int choice;
    std::cout << "Choose Micromouse type:\n1. Right Hand Rule\n2. Backtracking\n3. Laser Backtracking\n4. Lidar Backtracking\n";
    std::cin >> choice;
    switch (choice) {
        case 1:
            micromouse = std::make_shared<RightHandRuleMazeSolver>(maze);
            break;
        case 2:
            micromouse = std::make_shared<BacktrackingMazeSolver>(maze);
            break;
        case 3:
            micromouse = std::make_shared<LaserBacktrackingMazeSolver>(maze);
            break;
        case 4:
            micromouse = std::make_shared<LidarBacktrackingMazeSolver>(maze);
            break;
        default:
            std::cerr << "Invalid choice" << std::endl;
            return 1;
    }

    micromouse->initialize(); // Ensure that the sensor is initialized after the object is fully constructed


    auto simulator = std::make_unique<Simulator>(micromouse, maze);
    simulator->run();
   // Disable file output for logger
    logger->disableFileOutput();
    return 0;
}
