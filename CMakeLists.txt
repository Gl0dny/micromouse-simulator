cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(MicromouseProject)

# Wersja standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ścieżki do nagłówków
include_directories(include)

# Dodajemy wszystkie pliki źródłowe
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

# Tworzenie głównego pliku wykonywalnego
add_executable(MicromouseProject main.cpp ${SOURCES})

# # Dodajemy bibliotekę Qt5 (jeśli używasz Qt)
# find_package(Qt5 REQUIRED COMPONENTS Widgets)
# include_directories(${Qt5Widgets_INCLUDE_DIRS})
# target_link_libraries(MicromouseProject Qt5::Widgets)

# # Dodajemy testy
# add_executable(tests tests/test_main.cpp ${SOURCES})
# target_link_libraries(tests Qt5::Widgets)
# enable_testing()
# add_test(NAME tests COMMAND tests)
