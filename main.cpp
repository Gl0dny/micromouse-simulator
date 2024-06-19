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
    auto micromouse = std::make_shared<RightHandRuleMazeSolver>();

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

    auto simulator = std::make_unique<Simulator>(micromouse);
    simulator->run();

    return 0;
}


// #include "Utils.h"
// #include "Simulator.h"
// #include "Logger.h"
// #include <memory>
// #include <string>

// int main() {
//     std::string main_log_file = "./logs/main.log";
//     std::unique_ptr<Logger> logger = std::make_unique<Logger>(main_log_file);
//     int width = 21;
//     int height = 21;

//     std::string maze_log_file = "./logs/maze.log";

//     std::shared_ptr<Maze> maze = std::make_shared<Maze>(width, height, maze_log_file);
//     maze->generateMaze();

//     std::vector<std::unique_ptr<Micromouse>> mice;
//     mice.push_back(std::make_unique<MicromouseRightHandRule>(1, 1, maze));
//     mice.push_back(std::make_unique<MicromouseWithMemory>(1, 1, maze));
//     mice.push_back(std::make_unique<IntelligentMicromouse>(1, 1, maze));
//     mice.push_back(std::make_unique<SuperIntelligentMicromouse>(1, 1, maze));

//     for (auto& mouse : mice) {
//         Simulator simulator(width, height, maze_log_file, std::move(mouse));
//         logger->logMessage("Starting the simulation: ");
//         simulator.runSimulation();
//     }

//     logger->disableFileOutput();

//     return 0;
// }