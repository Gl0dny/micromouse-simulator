#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "Robot.h"

class Micromouse : public Robot {
public:
    Micromouse(int startX, int startY);
    void move() override;
    void updateSensors() override;
    void makeDecision() override;
};

#endif // MICROMOUSE_H

// Kod definiuje klasę Micromouse dziedziczącą po klasie Robot, dostosowaną do symulacji robota micromouse - poruszającego się po labiryncie. Wykorzystuje dziedziczenie i przesłanianie metod do dostosowania zachowań takich jak ruch, aktualizacje sensorów oraz podejmowanie decyzji specyficznych dla zadań robota micromouse.