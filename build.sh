#!/bin/bash

# Funkcja do sprawdzenia, czy CMake jest zainstalowany
check_cmake() {
    if ! command -v cmake &> /dev/null
    then
        echo "CMake nie jest zainstalowany. Zainstaluj CMake i spróbuj ponownie."
        exit 1
    fi
}

# Funkcja do sprawdzenia, czy Qt5 jest zainstalowany
check_qt() {
    if ! command -v qmake &> /dev/null
    then
        echo "Qt5 nie jest zainstalowany. Zainstaluj Qt5 i spróbuj ponownie."
        exit 1
    fi
}

# Funkcja do wyświetlania pomocy
show_help() {
    echo "Użycie: ./build.sh [opcje]"
    echo "Opcje:"
    echo "  --help     Wyświetla tę pomoc"
    echo "  --test     Buduje projekt i uruchamia tylko testy, bez uruchamiania głównej aplikacji"
    echo "  --clean    Czyści katalog build i wszystkie pliki wyjściowe"
    echo "  --debug    Buduje projekt w trybie debugowania"
}

# Funkcja do czyszczenia katalogu build i plików wyjściowych
clean_build() {
    echo "Czyszczenie katalogu build i wszystkich plików wyjściowych..."
    rm -rf build
    rm -rf logs
    rm -rf tests/logs
    if [ $? -ne 0 ]; then
        echo "Czyszczenie nie powiodło się."
        exit 1
    fi
    echo "Czyszczenie zakończone sukcesem."
}

# Funkcja do budowania projektu
build() {
    echo "Tworzenie katalogu build, jeśli nie istnieje..."
    if [ ! -d "build" ]; then
        mkdir build
    fi

    cd build || exit

    # Konfiguracja projektu za pomocą CMake
    echo "Konfiguracja projektu za pomocą CMake..."
    if $DEBUG; then
        cmake -DCMAKE_BUILD_TYPE=Debug ..
    else
        cmake ..
    fi

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

    cd ..
}

# Funkcja do uruchamiania aplikacji
run_application() {
    echo "Uruchamianie aplikacji..."
    ./build/MicromouseProject

    # Sprawdzenie, czy aplikacja została uruchomiona poprawnie
    if [ $? -ne 0 ]; then
        echo "Uruchomienie aplikacji nie powiodło się."
        exit 1
    fi
}

# Funkcja do uruchamiania testów
run_tests() {
    echo "Uruchamianie testów..."
    ./build/tests

    # Sprawdzenie, czy testy zakończyły się sukcesem
    if [ $? -ne 0 ]; then
        echo "Testy nie powiodły się."
        exit 1
    fi
    cd ..
}

# Flagi
CLEAN=false
TEST=false
DEBUG=false

# Parsowanie argumentów
for arg in "$@"
do
    case $arg in
        --clean)
        CLEAN=true
        shift # Usuwa argument
        ;;
        --test)
        TEST=true
        shift # Usuwa argument
        ;;
        --debug)
        DEBUG=true
        shift # Usuwa argument
        ;;
        --help)
        show_help
        exit 0
        ;;
        *)
        echo "Nieznany argument: $arg"
        show_help
        exit 1
        ;;
    esac
done

# Wykonywanie odpowiednich czynności na podstawie flag
if $CLEAN; then
    clean_build
fi

if $TEST; then
    build
    run_tests
else
    build
    run_application
fi
