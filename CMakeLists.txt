cmake_minimum_required(VERSION 3.10)

# Project name
project(MicromouseProject)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Włączenie automatycznego generowania plików MOC, RCC i UIC dla Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# If using Qt5, uncomment these lines and add the necessary components
find_package(Qt5 REQUIRED COMPONENTS Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Micromouse.cpp
    src/Robot.cpp
    src/Maze.cpp
    src/Sensor.cpp
    src/Simulator.cpp
    src/GUI.cpp
    src/Utils.cpp
    src/MainWindow.cpp
    src/MazeWidget.cpp
)

# Main executable
add_executable(MicromouseProject main.cpp ${SOURCES})

# Linkowanie bibliotek Qt5
target_link_libraries(MicromouseProject Qt5::Widgets)

# Test executable
add_executable(tests tests/test_maze.cpp ${SOURCES})

# Linkowanie bibliotek Qt5 do testów
target_link_libraries(tests Qt5::Widgets)

# Enable testing
enable_testing()
add_test(NAME maze_tests COMMAND tests)
