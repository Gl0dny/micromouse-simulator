#include "Maze.h"
#include "Utils.h"
#include <iostream>

Maze::Maze(int width, int height)
    : width(width), height(height), mazeGrid(width, std::vector<int>(height, 0)) {}

int Maze::getWidth() const { return width; }
int Maze::getHeight() const { return height; }
// void Maze::generateMaze() {
//     // Implementacja generowania labiryntu
//     // Przykład: Wczytanie labiryntu z pliku
//     auto lines = Utils::readFile("resources/maze_data.txt");
//     // Przetwarzanie danych z pliku, aby zainicjalizować mazeGrid

//     for (int y = 0; y < height && y < lines.size(); ++y) {
//         for (int x = 0; x < width && x < lines[y].size(); ++x) {
//             mazeGrid[x][y] = (lines[y][x] == '#') ? 1 : 0;
//         }
//     }
// }
void Maze::generateMaze() {
    // Przykład: Losowe generowanie labiryntu
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mazeGrid[x][y] = Utils::getRandomNumber(0, 1);
        }
    }
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
