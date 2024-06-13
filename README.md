Wstępny Opis Projektu: Symulacja Micromouse
1. Opis Projektu

Projekt zakłada stworzenie symulacji robota typu micromouse, którego zadaniem jest przejście przez labirynt. Robot będzie wyposażony w czujniki, które pozwolą mu zbierać dane o otoczeniu, i na ich podstawie podejmować decyzje dotyczące ruchu. Symulacja będzie zawierała wizualizację ruchu robota w labiryncie.
2. Funkcjonalność

    Generowanie i wyświetlanie labiryntu: Labirynt będzie generowany losowo lub wczytywany z pliku. Będzie wyświetlany w interfejsie użytkownika, pokazując zarówno ściany, jak i wolne przestrzenie.
    Symulacja ruchu robota: Robot będzie poruszał się po labiryncie, analizując dane z czujników i podejmując decyzje o kierunku ruchu. Ruch robota będzie wizualizowany na ekranie.
    Czujniki robota: Robot będzie wyposażony w czujniki odległości (na przód, lewo, prawo), które pozwolą mu ocenić odległość do najbliższej ściany w tych kierunkach.
    Algorytm nawigacji: Robot będzie używał prostych algorytmów nawigacji, takich jak śledzenie ściany, aby znaleźć wyjście z labiryntu. Algorytm będzie oparty na lokalnych danych z czujników.
    Interfejs użytkownika: Program będzie posiadał prosty graficzny interfejs użytkownika (GUI), umożliwiający uruchomienie symulacji, pauzowanie, resetowanie oraz modyfikowanie parametrów labiryntu i robota.
    Raportowanie postępów: Program będzie wyświetlał informacje o postępach robota, takie jak liczba kroków, odległość od celu, itp.

3. Szkic Interfejsu Użytkownika
3.1. Główne okno aplikacji

    Obszar wyświetlania labiryntu: Centralna część okna, gdzie będzie wyświetlany labirynt i pozycja robota.
    Panel kontrolny: Panel boczny zawierający przyciski sterujące:
        Start/Pauza: Rozpoczęcie lub zatrzymanie symulacji.
        Reset: Zresetowanie symulacji.
        Opcje: Ustawienia parametrów labiryntu i robota.

3.2. Diagram klas

    Micromouse: Klasa reprezentująca robota. Zawiera dane o położeniu, kierunku ruchu, stanach czujników oraz metodach podejmowania decyzji na podstawie lokalnych danych.
    Maze: Klasa reprezentująca labirynt. Zawiera informacje o strukturze labiryntu oraz metodach generowania i wyświetlania labiryntu.
    Simulator: Klasa odpowiedzialna za symulację, zawierająca metody do uruchamiania, pauzowania i resetowania symulacji oraz integrująca klasę Micromouse i Maze.
    GUI: Klasa obsługująca graficzny interfejs użytkownika, odpowiedzialna za rysowanie labiryntu i robota oraz obsługę interakcji użytkownika.

    --------------------------------------------------------
    |                         Panel Kontrolny              |
    |------------------------------------------------------|
    | Start | Pauza | Reset | Opcje                        |
    --------------------------------------------------------
    |                                                      |
    |                                                      |
    |               Obszar wyświetlania labiryntu          |
    |                                                      |
    |                                                      |
    --------------------------------------------------------

1. Struktura katalogów projektu

    MicromouseProject/
    ├── include/
    │   ├── Micromouse.h
    │   ├── Robot.h
    │   ├── Maze.h
    │   ├── Sensor.h
    │   ├── Simulator.h
    │   ├── GUI.h
    │   └── Utils.h
    ├── src/
    │   ├── Micromouse.cpp
    │   ├── Robot.cpp
    │   ├── Maze.cpp
    │   ├── Sensor.cpp
    │   ├── Simulator.cpp
    │   ├── GUI.cpp
    │   └── Utils.cpp
    ├── resources/
    │   ├── maze_data.txt 
    ├── tests/
    │   ├── test_main.cpp
    ├── docs/
    │   ├── doxygen_config (plik konfiguracyjny doxygen)
    ├── CMakeLists.txt
    └── README.md

Dependencies:


<!-- Plan implementacji z dziedziczeniem, polimorfizmem i szablonami
Zaimplementuj bazową klasę Robot oraz klasę pochodną Micromouse:
    Robot jako klasa abstrakcyjna.
    Micromouse jako klasa dziedzicząca po Robot.
Zaimplementuj klasę Maze: Zaimplementuj generowanie i wyświetlanie labiryntu.
Zaimplementuj klasę Simulator z użyciem polimorfizmu: Użyj polimorfizmu, aby klasa Simulator mogła współpracować z dowolnym typem robota dziedziczącym po klasie Robot.
Zaimplementuj klasę Sensor jako szablon:
    Utwórz szablon klasy Sensor.
    Zaimplementuj metody szablonu.
Zaimplementuj interfejs użytkownika: Użyj Qt do stworzenia GUI.
Testuj i debuguj: Utwórz testy jednostkowe i integracyjne w folderze tests.
Dokumentacja: Udokumentuj kod przy użyciu doxygen. -->