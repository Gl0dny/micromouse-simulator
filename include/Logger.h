#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger();
    void logMessage(const std::string &message);
    void enableFileOutput(const std::string &filePath, bool toFileOnly = false);
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
