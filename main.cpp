#include "Simulator.h"
#include "Micromouse.h"
#include <memory>
#include <iostream>
#include <string>

int main() {
    auto main_log_file = "./logs/main.log";
    auto logger = std::make_unique<Logger>(main_log_file);
    logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze: ");
    Maze* maze = Maze::getInstance();
    maze->displayMaze();
    maze->setLogger(main_log_file, false).displayMaze();

    auto micromouse = chooseMicromouse(maze);
    if (!micromouse) {
        return 1;
    }
    
    auto simulator = std::make_unique<Simulator>(micromouse, maze);
    simulator->run();

    logger->disableFileOutput();
    return 0;
}
