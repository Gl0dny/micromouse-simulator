#include "Maze.h"
#include "gtest/gtest.h"
#include <set>
#include <utility>

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
                    return true; // Additional walls found
                }
            }
        }
        return false;
    }

};

TEST_F(MazeTest, MazeGenerationMultipleTimes) {
    int width = 21;
    int height = 21;
    int trials = 10;

    for (int i = 0; i < trials; ++i) {
        Maze maze(width, height);
        maze.generateMaze();
        
        std::cout << "Generated Maze " << i + 1 << ":\n";
        
        if (hasAdditionalWalls(maze, width, height)) {
            std::cout << "Additional walls found in the maze on trial " << i + 1 << ":\n";
            maze.displayMaze();
        }

        EXPECT_FALSE(hasAdditionalWalls(maze, width, height));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
