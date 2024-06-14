#include "Maze.h"
#include "Utils.h"
#include <iostream>

int main() {
    // Utworzenie obiektu labiryntu o szerokości 5 i wysokości 3
    Maze maze(10, 10);

    // Generowanie labiryntu (z pliku lub losowe)
    maze.generateMaze();

    // Wyświetlenie wygenerowanego labiryntu
    std::cout << "Generated Maze:\n";
    maze.displayMaze();

    // Sprawdzenie, czy w określonych pozycjach są ściany
    std::cout << "\nChecking if certain positions are walls:\n";
    for (int y = 0; y < maze.getHeight(); ++y) {
        for (int x = 0; x < maze.getWidth(); ++x) {
            std::cout << "Position (" << x << ", " << y << ") is "
                      << (maze.isWall(x, y) ? "a wall." : "not a wall.") << '\n';
        }
    }

    return 0;
}
