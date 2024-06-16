#include "Utils.h"
#include <random>
#include <fstream>
#include <iostream>

namespace Utils {

    int getRandomNumber(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void clearFile(const std::string &filePath) {
        std::ofstream ofs(filePath, std::ios::trunc);
        if (ofs) {
            std::cout << "File cleared: " << filePath << std::endl;
        } else {
            std::cerr << "Failed to clear file: " << filePath << std::endl;
        }
    }

} // namespace Utils
