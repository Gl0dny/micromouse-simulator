#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    Logger();

    void logMessage(const std::string &message);
    void enableFileOutput(const std::string &filePath, bool toFileOnly = false);
    void disableFileOutput();
    void clearLogFile();

private:
    std::string getCurrentDateTime();
    void createLogDirectory(const std::string &filePath);

    std::ofstream logFile;
    bool logToFile;
    bool logToFileOnly;
    std::string logFilePath;
};

#endif // LOGGER_H
