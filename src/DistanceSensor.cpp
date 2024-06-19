// #include "DistanceSensor.h"

// DistanceSensor::DistanceSensor(std::shared_ptr<Maze> maze, int posX, int posY)
//     : Sensor<bool>(maze, posX, posY) {}

// void DistanceSensor::updateReadings(int posX, int posY) {
//     this->posX = posX;
//     this->posY = posY;

//     data[0] = maze->isWall(posX, posY - 1); // North
//     data[1] = maze->isWall(posX, posY + 1); // South
//     data[2] = maze->isWall(posX - 1, posY); // West
//     data[3] = maze->isWall(posX + 1, posY); // East
// }
