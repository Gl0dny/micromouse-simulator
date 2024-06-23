#include "Simulator.h"
#include "Maze.h"
#include "Micromouse.h"
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

int main() {
    auto main_log_file = "./logs/main.log";
    auto logger = std::make_unique<Logger>(main_log_file);
    logger->enableFileOutput(false).clearLogFile().logMessage("Creating the Maze...");
    Maze* maze = Maze::getInstance();
    maze->displayMaze();
    maze->setLogger(main_log_file, false).displayMaze();

    logger->logMessage("Creating the Micromouse...");
    auto micromouse = chooseMicromouse(maze);
    if (!micromouse) {
        return 1;
    }
    
    logger->logMessage("Creating the Simulator...");
    auto simulator = std::make_unique<Simulator>(micromouse, maze);

    std::atomic<bool> exitFlag(false);
    
    logger->logMessage("Running the simulation. Started a thread to handle user input for start/pause/reset/exit");
    std::thread inputThread([&simulator, &exitFlag]() {
        std::string command;
        std::cout << "Enter 'start' to start the simulation, 'pause' to pause it, 'reset' to reset it, or 'exit' to exit: \n";
        while (true) {
            std::cin >> command;
            if (command == "start") {
                simulator->start();
                std::cout << "Simulation started. You can pause it by entering 'pause'.\n";
            } else if (command == "pause") {
                simulator->pause();
            } else if (command == "reset") {
                simulator->reset();
            } else if (command == "exit") {
                simulator->pause();
                std::cout << "Exiting...\n";
                break;
            } else {
                simulator->pause();
                std::cout << "Unknown command. Please enter 'start', 'pause', 'reset', or 'exit'.\n";
            }
        }
    });

    inputThread.join();  // Wait for the input thread to finish
    logger->logMessage("Simulation finished.");
    logger->disableFileOutput();
    return 0;
}
