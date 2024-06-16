#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string &filePath);
    void logMessage(const std::string& message, bool includeTimestamp = true);
    void enableFileOutput(bool toFileOnly = true);
    void disableFileOutput();
    void clearLogFile();

private:
    bool logToFile;
    bool logToFileOnly;
    std::ofstream logFile;
    std::string logFilePath;

    void createLogDirectory(const std::string &filePath);
};

#endif // LOGGER_H
