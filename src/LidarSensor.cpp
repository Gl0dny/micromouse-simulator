// #include "LidarSensor.h"

// LidarSensor::LidarSensor(std::shared_ptr<Maze> maze, int posX, int posY)
//     : Sensor<bool>(maze, posX, posY) {}

// void LidarSensor::updateReadings(int posX, int posY) {
//     this->posX = posX;
//     this->posY = posY;

//     std::vector<std::pair<int, int>> offsets = {
//         {-1, -1}, {0, -1}, {1, -1}, 
//         {-1,  0}, {0,  0}, {1,  0}, 
//         {-1,  1}, {0,  1}, {1,  1}
//     };

//     for (size_t i = 0; i < offsets.size(); ++i) {
//         int nx = posX + offsets[i].first;
//         int ny = posY + offsets[i].second;
//         data[i] = maze->isWall(nx, ny);
//     }
// }
