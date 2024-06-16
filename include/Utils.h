#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <ctime>
#include <sys/stat.h>

namespace Utils {

    class Logger {
    public:
        Logger();

        void logMessage(const std::string &message);

        void enableFileOutput(const std::string &filePath, bool toFileOnly = false);

        void disableFileOutput();

    private:
        std::string getCurrentDateTime();
        void createLogDirectory(const std::string &filePath);
        void clearLogFile();

        std::ofstream logFile;
        bool logToFile;
        bool logToFileOnly;
        std::string logFilePath;
    };

    extern Logger logger;

    int getRandomNumber(int min, int max);

} // namespace Utils

#endif // UTILS_H
