#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <ctime>

namespace Utils {

    class Logger {
    public:
        Logger();

        void logMessage(const std::string &message);

        void enableFileOutput(const std::string &filePath, bool toFileOnly = false);

        void disableFileOutput();

    private:
        std::string getCurrentDateTime();

        std::ofstream logFile;
        bool logToFile;
        bool logToFileOnly;
    };

    extern Logger logger;

    int getRandomNumber(int min, int max);

} // namespace Utils

#endif // UTILS_H
