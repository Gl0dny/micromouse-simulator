#include "Logger.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

Logger::Logger(const std::string &filePath) :logFilePath(filePath),  logToFile(false), logToFileOnly(false) {
    createLogDirectory(logFilePath);
}

void Logger::logMessage(const std::string &message, bool includeTimestamp /* = true */) {
    std::string logEntry;

    if (includeTimestamp) {
        std::string timestamp = Utils::getCurrentDateTime();
        logEntry = "[" + timestamp + "] " + message;
    } else {
        logEntry = message;
    }

    if (logToFile) {
        logFile << logEntry << std::endl;
        if (!logToFileOnly) {
            std::cout << logEntry << std::endl;
        }
    } else {
        std::cout << logEntry << std::endl;
    }
}



void Logger::enableFileOutput(bool toFileOnly /* = true */) {
    std::cout << "Checking if log file exists: " << logFilePath << std::endl;

    Utils::fileExists(logFilePath);

    logFile.open(logFilePath, std::ios::out | std::ios::app);
    if (logFile.is_open()) {
        logToFile = true;
        logToFileOnly = toFileOnly;
        if (toFileOnly) {
            std::cout << "Logging to file only: " << logFilePath << std::endl;
        } else {
            std::cout << "Logging to both terminal and file: " << logFilePath << std::endl;
        }
    } else {
        std::cerr << "Unable to open log file: " << logFilePath << std::endl;
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

void Logger::createLogDirectory(const std::string &logFilePath) {
    std::string dirPath = logFilePath.substr(0, logFilePath.find_last_of("/"));
    Utils::createDirectory(dirPath);
}
