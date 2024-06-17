#include "Maze.h"
#include "gtest/gtest.h"
#include <set>
#include <string>
#include <memory>

class MazeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup can be used to initialize variables if needed
    }

    bool hasAdditionalWalls(const Maze& maze, int width, int height) {
        // We should check for any 2x2 blocks of walls inside the maze
        for (int x = 1; x < width - 1; ++x) {
            for (int y = 1; y < height - 1; ++y) {
                if (maze.isWall(x, y) && maze.isWall(x + 1, y) && maze.isWall(x, y + 1) && maze.isWall(x + 1, y + 1)) {
                    return true;
                }
            }
        }
        return false;
    }
};

TEST_F(MazeTest, MazeGenerationMultipleTimes) {
    int width = 9;
    int height = 9;
    int trials = 100;

    for (int i = 0; i < trials; ++i) {
        std::string logFileName = "./tests/logs/maze_test_log_file_" + std::to_string(i + 1) + ".log";
        std::unique_ptr<Maze> maze = std::make_unique<Maze>(width, height, logFileName);
        maze->generateMaze();
        
        std::cout << "Generated Maze " << i + 1 << ":\n";
        
        if (hasAdditionalWalls(*maze, width, height)) {
            std::cout << "Additional walls found in the maze on trial " << i + 1 << ":\n";
            maze->setLogger(logFileName, false);
            maze->displayMaze();
        }
        else{
            maze->displayMaze();
        }

        EXPECT_FALSE(hasAdditionalWalls(*maze, width, height));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
