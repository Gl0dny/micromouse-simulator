# Enable testing
enable_testing()

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
add_executable(tests test_maze.cpp ${CMAKE_SOURCE_DIR}/src/Maze.cpp ${CMAKE_SOURCE_DIR}/src/Logger.cpp ${CMAKE_SOURCE_DIR}/src/Utils.cpp ${CMAKE_SOURCE_DIR}/src/Micromouse.cpp ${CMAKE_SOURCE_DIR}/src/Sensor.cpp ${CMAKE_SOURCE_DIR}/src/Simulator.cpp)

# Link Google Test and pthread for tests
target_link_libraries(tests GTest::GTest GTest::Main pthread)

# Add the tests
add_test(NAME maze_tests COMMAND tests)
