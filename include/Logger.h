#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string &filePath);
    Logger& logMessage(const std::string& message, bool includeTimestamp = true);
    Logger& enableFileOutput(bool toFileOnly = true);
    Logger& disableFileOutput();
    Logger& clearLogFile();

private:
    bool logToFile;
    bool logToFileOnly;
    std::ofstream logFile;
    std::string logFilePath;

    void createLogDirectory(const std::string &filePath);
};

#endif // LOGGER_H
