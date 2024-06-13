#include "Utils.h"
#include <fstream>
#include <iostream>
#include <random>

namespace Utils {

    std::vector<std::string> readFile(const std::string &fileName) {
        std::vector<std::string> lines;
        std::ifstream file(fileName);

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        } else {
            logMessage("Unable to open file: " + fileName);
        }

        return lines;
    }

    int getRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void logMessage(const std::string &message) {
        std::cout << "[LOG] " << message << std::endl;
    }

} // namespace Utils
