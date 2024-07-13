#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

/**
 * @brief The Logger class provides functionality for logging messages to a file and/or console. It allows messages to be logged with optional timestamps and supports enabling or disabling file output. The class includes methods for clearing the log file and managing logging behavior between file and console outputs. The Logger ensures efficient file handling and robust logging capabilities, aiding in debugging, monitoring, and analysis tasks within an application.
 */
class Logger {
public:
    /**
     * @brief Constructor for Logger.
     * @param filePath Path to the log file.
     */
    Logger(const std::string &filePath);

    /**
     * @brief Destructor for Maze.
     */
    ~Logger();

    /**
     * @brief Logs a message.
     * @param message The message to log.
     * @param includeTimestamp Whether to include a timestamp.
     * @return Reference to the Logger object.
     */
    Logger& logMessage(const std::string& message, bool includeTimestamp = true);

    /**
     * @brief Enables file output for logging.
     * @param toFileOnly Whether to log only to the file.
     * @return Reference to the Logger object.
     */
    Logger& enableFileOutput(bool toFileOnly = true);

    /**
     * @brief Clears the log file.
     * @return Reference to the Logger object.
     */
    Logger& clearLogFile();

private:
    bool logToFile; ///< Indicates if logging to file is enabled.
    bool logToFileOnly; ///< Indicates if logging to file only is enabled.
    std::ofstream logFile; ///< Output file stream for logging.
    std::string logFilePath; ///< Path to the log file.

    /**
     * @brief Creates the log directory if it doesn't exist.
     * @param filePath Path to the log file.
     */
    void createLogDirectory(const std::string &filePath);

        /**
     * @brief Disables file output for logging.
     * @return Reference to the Logger object.
     */
    void disableFileOutput();
};

#endif // LOGGER_H
