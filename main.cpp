#include "Utils.h"
#include "Maze.h"
#include "Logger.h"
#include <memory> // for smart pointers

int main() {
    std::string main_log_file = "./logs/main.log";

    std::unique_ptr<Logger> logger= std::make_unique<Logger>();

    // Enable file logging (both terminal and file)
    logger->enableFileOutput(main_log_file);
    logger->clearLogFile();

    int width = 21;
    int height = 21;

    logger->logMessage("Creating the Maze: ");

    // Using smart pointer for Maze object
    std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height);
    maze->generateMaze();
    maze->displayMaze();

    // logger->enableFileOutput(log_file, true);
    logger->disableFileOutput();

    return 0;
}
