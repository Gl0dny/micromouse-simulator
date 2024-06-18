#include "Simulator.h"
#include "RightHandRuleMazeSolver.h"
#include <memory>
#include <iostream>
// #include <string>

int main() {
    // std::string main_log_file = "./logs/main.log";
    // std::unique_ptr<Logger> logger = std::make_unique<Logger>(main_log_file);
    // int width = 21;
    // int height = 21;
    
    // // Creating a unique log file name for the maze
    // std::string maze_log_file = "./logs/maze.log";
    // std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height, maze_log_file);

    // // Logging initialization
    // logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze: ");
    
    // // Generating and displaying the maze
    // maze->generateMaze().displayMaze();
    
    // // Setting the logger and displaying the maze again
    // maze->setLogger(main_log_file, false).displayMaze();

    // // Disable file output for logger
    // logger->disableFileOutput();
    std::unique_ptr<Micromouse> micromouse = std::make_unique<RightHandRuleMazeSolver>();;

        // Choose the type of Micromouse
    // int choice;
    // std::cout << "Choose Micromouse type:\n1. Right Hand Rule\n2. With Memory\n3. Intelligent\n4. Advanced Intelligent\n";
    // std::cin >> choice;
    // switch (choice) {
    //     case 1:
    //         micromouse = std::make_unique<MicromouseRightHandRule>();
    //         break;
    //     case 2:
    //         micromouse = std::make_unique<MicromouseWithMemory>();
    //         break;
    //     case 3:
    //         micromouse = std::make_unique<IntelligentMicromouse>();
    //         break;
    //     case 4:
    //         micromouse = std::make_unique<AdvancedIntelligentMicromouse>();
    //         break;
    //     default:
    //         std::cerr << "Invalid choice" << std::endl;
    //         return 1;
    // }

    Simulator simulator(*micromouse);
    simulator.run();

    return 0;
}
