#include "Logger.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

Logger::Logger() : logToFile(false), logToFileOnly(false) {}

void Logger::logMessage(const std::string &message) {
    std::string timestamp = Utils::getCurrentDateTime();
    std::string logEntry = "[" + timestamp + "] " + message;

    if (logToFile) {
        logFile << logEntry << std::endl;
        if (!logToFileOnly) {
            std::cout << logEntry << std::endl;
        }
    } else {
        std::cout << logEntry << std::endl;
    }
}

void Logger::enableFileOutput(const std::string &filePath, bool toFileOnly) {
    createLogDirectory(filePath);
    logFilePath = filePath;

    std::cout << "Checking if log file exists: " << filePath << std::endl;

    if (std::ifstream(filePath)) {
        std::cout << "Log file exists." << std::endl;
    } else {
        std::cout << "Log file does not exist." << std::endl;
    }

    logFile.open(filePath, std::ios::out | std::ios::app);
    if (logFile.is_open()) {
        logToFile = true;
        logToFileOnly = toFileOnly;
        if (toFileOnly) {
            std::cout << "Logging to file only: " << filePath << std::endl;
        } else {
            std::cout << "Logging to both terminal and file: " << filePath << std::endl;
        }
    } else {
        std::cerr << "Unable to open log file: " << filePath << std::endl;
    }
}

void Logger::disableFileOutput() {
    if (logFile.is_open()) {
        logFile.close();
    }
    logToFile = false;
    logToFileOnly = false;
    std::cout << "File logging disabled. Logging to terminal only." << std::endl;
}

void Logger::clearLogFile() {
    Utils::clearFile(logFilePath);
}

void Logger::createLogDirectory(const std::string &filePath) {
    std::string dirPath = filePath.substr(0, filePath.find_last_of("/"));
    Utils::createDirectory(dirPath);
}
