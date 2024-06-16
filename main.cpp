#include "Utils.h"

int main() {
    Utils::logger.logMessage("This is a test log message.");

    // Enable file logging (both terminal and file)
    Utils::logger.enableFileOutput("./logs/main.log");

    Utils::logger.logMessage("Logging to both terminal and file.");

    // Enable file logging (file only)
    Utils::logger.enableFileOutput("./logs/main.log", true);

    Utils::logger.logMessage("Logging to file only.");

    // Disable file logging
    Utils::logger.disableFileOutput();

    Utils::logger.logMessage("Logging to terminal only again.");

    // Generate a random number
    int randomNum = Utils::getRandomNumber(1, 100);
    Utils::logger.logMessage("Generated random number: " + std::to_string(randomNum));

    return 0;
}
