#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    int getRandomNumber(int min, int max);
    void clearFile(const std::string &filePath);
    std::string getCurrentDateTime();
}

#endif // UTILS_H
