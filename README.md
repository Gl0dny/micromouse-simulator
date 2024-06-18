Wstępny Opis Projektu: Symulacja Micromouse

1. Opis Projektu

<!-- TODO

Simulator:
'odświeżanie' symulacji -> prowadzenie działania myszy w gotowym labiryncie?
Robot / Micromouse / DecisionAlgorithm -> Mysz ma specyficzne zachowania wg. określone DecisionAlgorithm , robot to tylko abtract class
polimorfizm -> inne roboty? dwie myszy? dwa algorytmy?
micromouse Simple algorithm: follow the right-hand rule
micromouse that knows that its in the corner
micromouse with memory
intelligent micromouse ( memory + she knows that its in the corner )
Sensor / Distance sensor -> sensor to template dla różnych typów danych sensorów gdzie Distance sensor to specific sensor?
Zrozum gtest config zakomentowany
Rozdziel testy
Zaimplementuj interfejs użytkownika: Użyj Qt do stworzenia GUI.
Dokumentacja: Udokumentuj kod przy użyciu doxygen.

Napraw pojawianie się walli dodatkowych w maze: parzysta liczba w ścianie;
# # # # # # # # #
#   #
#   # # #   #   #
#           #   #
# # # # # # #   #
#               #
# # # # # # # # #
# # # # # # # # #

# # # # # # # #
#           # #
# # # # #   # #
        #   # #
#   #   #   # #
#   #   #   # #
#   #   #   # #
#   #       # #
# # # # # # # #

Można poprawić ale specyfika labiryntu ( korytarz musi być otoczony więc liczbą wyboru korytarza musi być liczba nieparzysta ( indeksowanie od 0 ), w przypadku parzystej liczby wyboru zawsze w labiryncie musiałbym pozwolić na istnieje podwójnych ścian - zakaz podwójnych ścian to założenie labiryntu i jego testów ). Mógłbym sztucznie wyżłobić pojedyncze ślepe uliczki ( sprawdzając trzy kierunki dookoła podwójnej ściany i decydując, że da się ją wyżłobić poza algorytmem depth-first search ) na długość jednego kroku ale mija się to ze specyfiką labiryntu. Pozostawiam hardcoded odd number of width/height.
  -->

Projekt zakłada stworzenie symulacji robota typu micromouse, którego zadaniem jest przejście przez labirynt. Robot będzie wyposażony w czujniki, które pozwolą mu zbierać dane o otoczeniu, i na ich podstawie podejmować decyzje dotyczące ruchu. Symulacja będzie zawierała wizualizację ruchu robota w labiryncie.

2.  Funkcjonalność

    Generowanie i wyświetlanie labiryntu: Labirynt będzie generowany losowo lub wczytywany z pliku. Będzie wyświetlany w interfejsie użytkownika, pokazując zarówno ściany, jak i wolne przestrzenie.
    Symulacja ruchu robota: Robot będzie poruszał się po labiryncie, analizując dane z czujników i podejmując decyzje o kierunku ruchu. Ruch robota będzie wizualizowany na ekranie.
    Czujniki robota: Robot będzie wyposażony w czujniki odległości (na przód, lewo, prawo), które pozwolą mu ocenić odległość do najbliższej ściany w tych kierunkach.
    Algorytm nawigacji: Robot będzie używał prostych algorytmów nawigacji, takich jak śledzenie ściany, aby znaleźć wyjście z labiryntu. Algorytm będzie oparty na lokalnych danych z czujników.
    Interfejs użytkownika: Program będzie posiadał prosty graficzny interfejs użytkownika (GUI), umożliwiający uruchomienie symulacji, pauzowanie, resetowanie oraz modyfikowanie parametrów labiryntu i robota.
    Raportowanie postępów: Program będzie wyświetlał informacje o postępach robota, takie jak liczba kroków, odległość od celu, itp.

3.  Szkic Interfejsu Użytkownika
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
   ├── CMakeLists.txt
   ├── include/
   │ ├── MainWindow.h
   │ ├── MazeWidget.h
   │ ├── Micromouse.h
   │ ├── Robot.h
   │ ├── Maze.h
   │ ├── Sensor.h
   │ ├── Simulator.h
   │ ├── GUI.h
   │ └── Utils.h
   ├── src/
   │ ├── MainWindow.cpp
   │ ├── MazeWidget.cpp
   │ ├── Micromouse.cpp
   │ ├── Robot.cpp
   │ ├── Maze.cpp
   │ ├── Sensor.cpp
   │ ├── Simulator.cpp
   │ ├── GUI.cpp
   │ └── Utils.cpp
   ├── main.cpp
   └── build.sh

Dependencies:

###### QT5

sudo apt install qt5-default

###### Google Test

git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install

## Opis diagramu:

    Simulator: Zarządza instancjami Maze i Robot, oraz kontroluje symulację.
    Maze: Reprezentuje labirynt, zawiera siatkę z komórkami labiryntu oraz metody do generowania i wyświetlania labiryntu.
    Robot: Reprezentuje robota w labiryncie, przechowuje jego pozycję oraz sensory.
    Sensor: Reprezentuje czujnik robota, wykrywa otoczenie.
    GUI: Odpowiada za wyświetlanie labiryntu i robota, ale w tej strukturze jest to klasa abstrakcyjna, bardziej jak koncept.
    MainWindow: Główne okno aplikacji Qt, zawiera widget labiryntu oraz instancję symulatora.
    MazeWidget: Widget odpowiedzialny za rysowanie labiryntu i robota.
    Utils: Zawiera funkcje pomocnicze, takie jak czytanie plików, generowanie liczb losowych oraz logowanie wiadomości.

```mermaid
classDiagram
    class Simulator {
        -Maze maze
        -Robot robot
        +start()
        +reset()
        +getMaze() : Maze
        +getRobot() : Robot
    }

    class Maze {
        -int width
        -int height
        -vector~vector~int~~ mazeGrid
        +Maze(int width, int height)
        +generateMaze()
        +isWall(int x, int y) : bool
        +displayMaze()
        +getWidth() : int
        +getHeight() : int
    }

    class Robot {
        -int x
        -int y
        -vector~Sensor~ sensors
        +Robot(int startX, int startY)
        +move()
        +getX() : int
        +getY() : int
        +addSensor(Sensor* sensor)
    }

    class Sensor {
        +detect() : int
        +getType() : string
    }

    class GUI {
        +displayMaze(Maze* maze)
        +displayRobot(Robot* robot)
    }

    class MainWindow {
        -MazeWidget* mazeWidget
        -Simulator* simulator
        +MainWindow(QWidget* parent = nullptr)
        +~MainWindow()
        +startSimulation()
        +resetSimulation()
    }

    class MazeWidget {
        -Simulator* simulator
        +MazeWidget(QWidget* parent = nullptr, Simulator* simulator = nullptr)
        +paintEvent(QPaintEvent* event)
    }

    class Utils {
        +readFile(const string &fileName) : vector~string~
        +getRandomNumber(int min, int max) : int
        +logMessage(const string &message)
    }

    Simulator --> Maze : uses
    Simulator --> Robot : uses
    Simulator --> GUI : uses
    Maze --> Utils : uses
    Robot --> Sensor : contains
    MainWindow --> Simulator : contains
    MainWindow --> MazeWidget : contains
    MazeWidget --> Simulator : uses

```
