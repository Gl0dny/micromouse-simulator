#include "Utils.h"

int main() {

    std::string log_file="./logs/main.log";

    // Enable file logging (both terminal and file)
    Utils::logger.enableFileOutput(log_file);
    Utils::logger.clearLogFile();




    // Utils::logger.enableFileOutput(log_file, true);
    Utils::logger.disableFileOutput();
    return 0;
}
