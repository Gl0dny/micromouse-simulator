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

    bool hasAdditionalWalls(const Maze* maze) {
        // We should check for any 2x2 blocks of walls inside the maze
        for (int x = 1; x < maze->getWidth() - 1; ++x) {
            for (int y = 1; y < maze->getHeight() - 1; ++y) {
                if (maze->isWall(x, y) && maze->isWall(x + 1, y) && maze->isWall(x, y + 1) && maze->isWall(x + 1, y + 1)) {
                    return true;
                }
            }
        }
        return false;
    }
};

TEST_F(MazeTest, MazeGenerationMultipleTimes) {
        Maze* maze = Maze::getInstance();
        
        if (hasAdditionalWalls(maze)) {
            std::cout << "Additional walls found in the maze " << ":\n";
            maze->setLogger("./logs/maze.log", false).displayMaze(); 
        }
        else{
            maze->displayMaze();
        }

        EXPECT_FALSE(hasAdditionalWalls(maze));
    }

TEST_F(MazeTest, Singleton) {
    Maze* maze1 = Maze::getInstance();
    Maze* maze2 = Maze::getInstance();
    EXPECT_EQ(maze1, maze2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
