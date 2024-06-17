#include "Utils.h"
#include "Maze.h"
#include "Logger.h"
#include <memory>
#include <string>

int main() {
    std::string main_log_file = "./logs/main.log";
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(main_log_file);
    int width = 21;
    int height = 21;
    
    // Creating a unique log file name for the maze
    std::string maze_log_file = "./logs/maze.log";
    std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height, maze_log_file);

    // Logging initialization
    logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze: ");
    
    // Generating and displaying the maze
    maze->generateMaze().displayMaze();
    
    // Setting the logger and displaying the maze again
    maze->setLogger(main_log_file, false).displayMaze();

    // Disable file output for logger
    logger->disableFileOutput();

    return 0;
}
