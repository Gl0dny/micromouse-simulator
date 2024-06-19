// #include "LaserSensor.h"

// LaserSensor::LaserSensor(std::shared_ptr<Maze> maze, int posX, int posY)
//     : Sensor<int>(maze, posX, posY) {}

// void LaserSensor::updateReadings(int posX, int posY)
// {
//     this->posX = posX;
//     this->posY = posY;

//     data[0] = 0; // North
//     data[1] = 0; // South
//     data[2] = 0; // West
//     data[3] = 0; // East

//     for (int i = posY - 1; i >= 0 && !maze->isWall(posX, i); --i)
//     {
//         ++data[0];
//     }
//     for (int i = posY + 1; i < maze->getHeight() && !maze->isWall(posX, i); ++i)
//     {
//         ++data[1];
//     }
//     for (int i = posX - 1; i >= 0 && !maze->isWall(i, posY); --i)
//     {
//         ++data[2];
//     }
//     for (int i = posX + 1; i < maze->getWidth() && !maze->isWall(i, posY); ++i)
//     {
//         ++data[3];
//     }
// }
