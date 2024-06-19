#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse()
    : posX(1), posY(1), direction("North") {}

int Micromouse::getPosX() const {
    return posX;
}

int Micromouse::getPosY() const {
    return posY;
}

void Micromouse::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void Micromouse::move() {
    readSensors();
    makeDecision();
    if (direction == "North") {
        posY--;
    } else if (direction == "East") {
        posX++;
    } else if (direction == "South") {
        posY++;
    } else if (direction == "West") {
        posX--;
    }
}



// void Micromouse::logMovement(int newX, int newY) {
//     route.emplace_back(newX, newY);
// }

// void Micromouse::saveRouteToFile(const std::string& filename) const {
//     std::ofstream outFile(filename);
//     if (outFile.is_open()) {
//         for (const auto& position : route) {
//             outFile << position.first << "," << position.second << std::endl;
//         }
//     }
//     outFile.close();
// }

