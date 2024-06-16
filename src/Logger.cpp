#include "Logger.h"
#include <iostream>
#include <ctime>
#include <sys/stat.h>

Logger::Logger() : logToFile(false), logToFileOnly(false) {}

void Logger::logMessage(const std::string &message) {
    std::string timestamp = getCurrentDateTime();
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

std::string Logger::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

void Logger::createLogDirectory(const std::string &filePath) {
    std::string dirPath = filePath.substr(0, filePath.find_last_of("/\\"));
    struct stat info;

    if (stat(dirPath.c_str(), &info) != 0) {
        // Directory does not exist
        if (mkdir(dirPath.c_str(), 0777) == -1) {
            std::cerr << "Error creating directory: " << dirPath << std::endl;
        } else {
            std::cout << "Created directory." << std::endl;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << dirPath << " is not a directory" << std::endl;
    }
}

void Logger::clearLogFile() {
    std::ofstream ofs(logFilePath, std::ios::trunc);
    if (ofs) {
        std::cout << "Log file cleared: " << logFilePath << std::endl;
    } else {
        std::cerr << "Failed to clear log file: " << logFilePath << std::endl;
    }
}
