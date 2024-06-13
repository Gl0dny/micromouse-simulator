#include "Maze.h"
#include <iostream>

Maze::Maze(int width, int height)
    : width(width), height(height), mazeGrid(width, std::vector<int>(height, 0)) {}

void Maze::generateMaze() {
    // Implementacja generowania labiryntu
}

bool Maze::isWall(int x, int y) const {
    // Zwróć true jeśli podana pozycja jest ścianą
    return mazeGrid[x][y] == 1;
}

void Maze::displayMaze() const {
    // Implementacja wyświetlania labiryntu
    for (const auto& row : mazeGrid) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}



// int main() {
//     // Utworzenie obiektu labiryntu o szerokości 5 i wysokości 3
//     Maze maze(5, 3);

//     // Przykładowe wypełnienie labiryntu (wartości losowe dla celów demonstracyjnych)
//     maze.displayMaze();

//     return 0;
// }

// # # # # # 
// #       # 
// # # # # #