#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

class Robot {
public:
    Robot(int startX, int startY);
    virtual void move() = 0;
    virtual void updateSensors() = 0;
    virtual void makeDecision() = 0;
    int getX() const;
    int getY() const;

protected:
    int posX, posY;
    int direction; // 0 - North, 1 - East, 2 - South, 3 - West
    std::vector<int> sensorData; // distance readings
};

#endif // ROBOT_H


// Klasa Robot jest abstrakcyjną klasą bazową dla robotów, z zadeklarowanymi metodami czysto wirtualnymi, które muszą być zaimplementowane w klasach pochodnych. Posiada pola przechowujące pozycję robota i kierunek oraz wektor na dane z czujników. Konstruktor klasy ustawia początkową pozycję robota, a metody dostępowe pozwalają na odczytanie aktualnych współrzędnych.