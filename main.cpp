#include "Utils.h"
#include "Maze.h"
#include "Logger.h"
#include <memory>

int main() {
    std::string main_log_file = "./logs/main.log";
    std::string maze_log_file = "./logs/maze.log";
    std::unique_ptr<Logger> logger= std::make_unique<Logger>(main_log_file);
    int width = 8;
    int height = 8;
    std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height);

    logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze: ");
    maze->generateMaze().displayMaze();
    maze->setLogger(main_log_file, false).displayMaze();

    logger->disableFileOutput();
    return 0;
}
