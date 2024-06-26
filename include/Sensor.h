#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <utility>
#include "Maze.h"
#include "Logger.h"

/**
 * @brief Base class for sensors.
 */
class Sensor {
public:
    /**
     * @brief Constructor for Sensor.
     * @param maze Pointer to the Maze object.
     * @param name Name of the sensor.
     */
    Sensor(Maze* maze, const std::string& name);

    /**
     * @brief Virtual destructor for Sensor.
     */
    virtual ~Sensor();

    /**
     * @brief Pure virtual function to get sensor data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    virtual void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const = 0;

protected:
    Maze* maze; ///< Pointer to the maze object.
    std::map<std::pair<int, int>, std::string> directionNames; ///< Map of direction names.
    std::unique_ptr<Logger> logger; ///< Logger object.
    int steps; ///< Step counter.
};

/**
 * @brief Class for distance sensor.
 */
class DistanceSensor : public Sensor {
public:
    /**
     * @brief Constructor for DistanceSensor.
     * @param maze Pointer to the Maze object.
     */
    DistanceSensor(Maze* maze);

    /**
     * @brief Function to get sensor data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

/**
 * @brief Class for laser sensor.
 */
class LaserSensor : public Sensor {
public:
    /**
     * @brief Constructor for LaserSensor.
     * @param maze Pointer to the Maze object.
     */
    LaserSensor(Maze* maze);

    /**
     * @brief Function to get sensor data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

/**
 * @brief Class for lidar sensor.
 */
class LidarSensor : public Sensor {
public:
    /**
     * @brief Constructor for LidarSensor.
     * @param maze Pointer to the Maze object.
     */
    LidarSensor(Maze* maze);

    /**
     * @brief Function to get sensor data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

#endif // SENSOR_H
