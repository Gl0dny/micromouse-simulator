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
    maze->displayMaze();
    maze->setLogger(main_log_file, false).displayMaze();

   // Choose Micromouse and Sensor using the new function
    auto micromouse = chooseMicromouse(maze);
    if (!micromouse) {
        return 1; // Exit if an invalid choice was made
    }
    
    auto simulator = std::make_unique<Simulator>(micromouse, maze);
    simulator->run();
   // Disable file output for logger
    logger->disableFileOutput();
    return 0;
}
