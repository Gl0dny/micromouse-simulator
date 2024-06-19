#include "Micromouse.h"
#include <iostream>

Micromouse::Micromouse()
    : posX(1), posY(1){}
    // , direction(0) {}
    // {    route.emplace_back(x, y); // log initial position}

// Micromouse::Micromouse(int startX, int startY, std::shared_ptr<Maze> maze)
//     : Robot(startX, startY), startX(startX), startY(startY),
//       distanceSensor(std::make_unique<DistanceSensor>(maze, startX, startY)),
//       advancedLaserSensor(std::make_unique<AdvancedLaserSensor>(maze, startX, startY)),
//       lidarSensor(std::make_unique<LIDARSensor>(maze, startX, startY)) {}

// void Micromouse::move() {
//     switch (direction) {
//         case 0: posY--; break; // North
//         case 1: posX++; break; // East
//         case 2: posY++; break; // South
//         case 3: posX--; break; // West
//     }
// }

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