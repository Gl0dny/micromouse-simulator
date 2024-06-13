#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace Utils {
    // Funkcja do wczytywania danych z pliku
    std::vector<std::string> readFile(const std::string &fileName);

    // Funkcja do losowego generowania liczb w zakresie [min, max]
    int getRandomNumber(int min, int max);

    // Funkcja do logowania wiadomości na konsolę
    void logMessage(const std::string &message);
}

#endif // UTILS_H


// pomocnicze funkcje, które będą wykorzystywane w różnych częściach projektu. Mogą to być funkcje do obsługi wejścia/wyjścia, logowania, losowego generowania liczb (np. do generowania labiryntu), czy też inne narzędzia, które nie pasują bezpośrednio do innych klas.