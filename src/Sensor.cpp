#include "Sensor.h"
#include <iostream>

Sensor::Sensor(std::shared_ptr<Maze> maze)
    : maze(maze) {     
        directionNames = {
        {{-1, 0}, "West"},  
        {{1, 0}, "East"},   
        {{0, -1}, "South"}, 
        {{0, 1}, "North"}   
    }; 
    }
    

DistanceSensor::DistanceSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void DistanceSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    knownMaze[x][y] = 0;

    // Check for walls in each direction
    for (const auto& [coordinates, direction] : directionNames) {
        int nx = x + coordinates.first;
        int ny = y + coordinates.second;

        // Debugging output for coordinates and direction
        std::cout << "Checking direction " << direction << " at (" << nx << ", " << ny << ")" << std::endl;

        if (nx >= 0 && ny >= 0 && nx < knownMaze.size() && ny < knownMaze[0].size()) {
            if (maze->isWall(nx, ny)) {
                knownMaze[nx][ny] = 1;
                std::cout << "Wall detected to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
            } else {
                knownMaze[nx][ny] = 0;
                std::cout << "No wall detected to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
            }
        } else {
            std::cout << "Out of bounds to the " << direction << " at (" << nx << ", " << ny << ")" << std::endl;
        }
    }
}


LaserSensor::LaserSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void LaserSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    for (const auto& dir : directions) {
        int nx = x;
        int ny = y;
        while (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight() && !maze->isWall(nx + dir.first, ny + dir.second)) {
            nx += dir.first;
            ny += dir.second;
            knownMaze[nx][ny] = 0;
        }
        if (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight()) {
            knownMaze[nx + dir.first][ny + dir.second] = 1;
        }
    }
}

LidarSensor::LidarSensor(std::shared_ptr<Maze> maze)
    : Sensor(maze) {}

void LidarSensor::getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze) const {
    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {0, -1}, {1, -1}, 
        {-1, 0},           {1, 0}, 
        {-1, 1}, {0, 1}, {1, 1}
    };
    for (const auto& dir : directions) {
        for (int step = 1; step <= 2; ++step) {
            int nx = x + dir.first * step;
            int ny = y + dir.second * step;
            if (nx >= 0 && ny >= 0 && nx < maze->getWidth() && ny < maze->getHeight()) {
                if (maze->isWall(nx, ny)) {
                    knownMaze[nx][ny] = 1;
                } else {
                    knownMaze[nx][ny] = 0;
                }
            }
        }
    }
}
