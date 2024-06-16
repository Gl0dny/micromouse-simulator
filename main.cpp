#include "Utils.h"
#include "Maze.h"

int main() {

    std::string main_log_file="./logs/main.log";
    std::string maze_log_file="./logs/maze.log";


    // Enable file logging (both terminal and file)
    Utils::logger.enableFileOutput(main_log_file);
    Utils::logger.clearLogFile();

    int width = 21;
    int height = 21;

    Utils::logger.logMessage("Creating the Maze: ");
    Utils::logger.disableFileOutput();
    Utils::logger.enableFileOutput(maze_log_file, true);
    Utils::logger.clearLogFile();
    Maze maze(width, height);
    maze.generateMaze();
    maze.displayMaze();



    // Utils::logger.enableFileOutput(log_file, true);
    Utils::logger.disableFileOutput();
    return 0;
}
