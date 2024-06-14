#!/bin/bash

# Sprawdzenie, czy CMake jest zainstalowany
if ! command -v cmake &> /dev/null
then
    echo "CMake nie jest zainstalowany. Zainstaluj CMake i spróbuj ponownie."
    exit 1
fi

# # Sprawdzenie, czy Qt5 jest zainstalowany
# if ! command -v qmake &> /dev/null
# then
#     echo "Qt5 nie jest zainstalowany. Zainstaluj Qt5 i spróbuj ponownie."
#     exit 1
# fi

# Tworzenie katalogu build, jeśli nie istnieje
if [ ! -d "build" ]; then
    mkdir build
fi

# Przejście do katalogu build
cd build

# Konfiguracja projektu za pomocą CMake
echo "Konfiguracja projektu za pomocą CMake..."
cmake ..

# Sprawdzenie, czy konfiguracja zakończyła się sukcesem
if [ $? -ne 0 ]; then
    echo "Konfiguracja CMake nie powiodła się."
    exit 1
fi

# Kompilacja projektu
echo "Kompilacja projektu..."
make

# Sprawdzenie, czy kompilacja zakończyła się sukcesem
if [ $? -ne 0 ]; then
    echo "Kompilacja projektu nie powiodła się."
    exit 1
fi

# Powrót do katalogu głównego
cd ..

# Uruchomienie aplikacji
echo "Uruchamianie aplikacji..."
./build/MicromouseProject

# Sprawdzenie, czy aplikacja została uruchomiona poprawnie
if [ $? -ne 0 ]; then
    echo "Uruchomienie aplikacji nie powiodło się."
    exit 1
fi
