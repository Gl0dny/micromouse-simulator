#include "Simulator.h"
#include "Micromouse.h"
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
            micromouse = createMicromouse<RightHandRuleMazeSolver, DistanceSensor>(maze);
            break;
        case 2:
            micromouse = createMicromouse<BacktrackingMazeSolver, DistanceSensor>(maze);
            break;
        case 3:
            micromouse = createMicromouse<LaserBacktrackingMazeSolver, LaserSensor>(maze);
            break;
        case 4:
            micromouse = createMicromouse<LidarBacktrackingMazeSolver, LidarSensor>(maze);
            break;
        default:
            std::cerr << "Invalid choice" << std::endl;
            return 1;
    }
    auto simulator = std::make_unique<Simulator>(micromouse, maze);
    simulator->run();
   // Disable file output for logger
    logger->disableFileOutput();
    return 0;
}
