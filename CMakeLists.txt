cmake_minimum_required(VERSION 3.10)

# Project name
project(MicromouseProject)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the debug flag based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE)
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Maze.cpp
    src/Logger.cpp
    src/Utils.cpp
    src/Micromouse.cpp
    src/Sensor.cpp
    src/Simulator.cpp
)

# Main executable
add_executable(MicromouseProject src/main.cpp ${SOURCES})

# Enable testing
enable_testing()

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
add_executable(tests tests/test_maze.cpp ${SOURCES})

# Link pthread for threads
target_link_libraries(MicromouseProject pthread)

# Link Google Test for tests
target_link_libraries(tests GTest::GTest GTest::Main)

# Add the tests
add_test(NAME maze_tests COMMAND tests)
