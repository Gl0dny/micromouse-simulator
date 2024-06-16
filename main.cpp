#include "Utils.h"
#include "Maze.h"
#include "Logger.h"
#include <memory> // for smart pointers

int main() {
    std::string main_log_file = "./logs/main.log";
    std::string maze_log_file = "./logs/maze.log";

    std::unique_ptr<Logger> logger= std::make_unique<Logger>(main_log_file);

    // Enable file logging (both terminal and file)
    logger->enableFileOutput(false);
    logger->clearLogFile();

    int width = 8;
    int height = 8;

    logger->logMessage("Creating the Maze: ");

    // Using smart pointer for Maze object
    std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height);
    maze->generateMaze();
    maze->setLogger(main_log_file, false);
    maze->displayMaze();

    // logger->enableFileOutput(log_file, true);
    logger->disableFileOutput();

    return 0;
}
