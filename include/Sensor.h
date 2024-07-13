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
 * @brief The Sensor class serves as a base class for different types of sensors used in a maze environment. It provides a common interface and shared functionality for sensor operations. The class maintains a reference to the Maze object, a map of direction names, a unique pointer to a Logger for logging activities, and a step counter. Derived classes must implement the pure virtual function getSensorData, which retrieves sensor data based on the maze's layout and updates a known representation of the maze. This design promotes modularity and ease of extending sensor capabilities.
 */
class Sensor {
public:
    /**
     * @brief Constructor for Sensor.
     * @param maze Reference to the Maze object.
     * @param name Name of the sensor.
     */
    Sensor(Maze& maze, const std::string& name);

    /**
     * @brief Virtual destructor for Sensor.
     */
    virtual ~Sensor() = default;

    /**
     * @brief Pure virtual function to get sensor data.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    virtual void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const = 0;

protected:
    /**
     * @brief Gets the reference to the Maze object.
     * @return Reference to the Maze object.
     */
    Maze& getMaze() const;

    /**
     * @brief Gets the direction names map.
     * @return Map of direction names.
     */
    const std::map<std::pair<int, int>, std::string>& getDirectionNames() const;

    /**
     * @brief Gets the logger object.
     * @return Pointer to the Logger object.
     */
    Logger* getLogger() const;

private:
    Maze& maze; ///< Reference to the maze object.
    std::map<std::pair<int, int>, std::string> directionNames; ///< Map of direction names.
    std::unique_ptr<Logger> logger; ///< Logger object.
    int steps; ///< Step counter.
};

/**
 * @brief The DistanceSensor class provides functionality to scan orthogonal directions from a starting position (x, y) within a maze. It uses a Maze object to query the environment and updates a 2D vector (knownMaze) to maintain a representation of the maze's layout based on sensor readings.
 */
class DistanceSensor : public Sensor {
public:
    /**
     * @brief Constructor for DistanceSensor.
     * @param maze Reference to the Maze object.
     */
    DistanceSensor(Maze& maze);

    /**
     * @brief The getSensorData function handles scanning for walls, logs detection results, and manages boundary conditions to ensure accurate mapping of the maze environment.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

/**
 * @brief The LaserSensor class provides functionality to scan multiple directions from a position (x, y) within a maze until the reading meets a wall. It uses a Maze object to query the environment and updates a 2D vector (knownMaze) to maintain a representation of the maze's layout based on sensor readings.
 */
class LaserSensor : public Sensor {
public:
    /**
     * @brief Constructor for LaserSensor.
     * @param maze Reference to the Maze object.
     */
    LaserSensor(Maze& maze);

    /**
     * @brief The getSensorData function handles scanning for walls in orthogonal directions, logs detection results, and manages boundary conditions, ensuring accurate mapping of the maze environment.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

/**
 * @brief The LidarSensor class provides functionality to detect walls and open spaces around a specific coordinate in a maze. It uses a Maze object to query the environment and updates a 2D vector (knownMaze) to maintain a representation of the maze's layout based on sensor readings.
 */
class LidarSensor : public Sensor {
public:
    /**
     * @brief Constructor for LidarSensor.
     * @param maze Reference to the Maze object.
     */
    LidarSensor(Maze& maze);

    /**
     * @brief The getSensorData function handles adjacent positions, logs detection results, and manages boundary conditions, ensuring accurate mapping of the maze environment.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param knownMaze 2D vector representing the known maze.
     * @param step Current step number.
     */
    void getSensorData(int x, int y, std::vector<std::vector<int>>& knownMaze, int step) const override;
};

#endif // SENSOR_H
