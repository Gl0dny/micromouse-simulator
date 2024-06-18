#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse()
    : posX(1), posY(1){}
    // , direction(0) {}
    // {    route.emplace_back(x, y); // log initial position}

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

void Micromouse::setStartingPosition(int x, int y) {
    startX = x;
    startY = y;
    posX = startX;
    posY = startY;
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

void Micromouse::move() {
    // switch (direction) {
    //     case 0: posY--; break; // North
    //     case 1: posX++; break; // East
    //     case 2: posY++; break; // South
    //     case 3: posX--; break; // West
    // }
}

bool Micromouse::hasReachedGoal() const {
    // Implementacja sprawdzenia czy mysz dotarła do celu
    return false; // Zmienić na odpowiednią logikę
}

void Micromouse::reset() {
    posX = startX;
    posY = startY;
    direction = 0; // Zresetowanie kierunku
}
