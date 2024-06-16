#include "Utils.h"

namespace Utils {

    Logger logger;

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
        logFile.open(filePath, std::ios::out | std::ios::app);
        if (logFile.is_open()) {
            logToFile = true;
            logToFileOnly = toFileOnly;
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
    }

    std::string Logger::getCurrentDateTime() {
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return buf;
    }

    int getRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

} // namespace Utils
