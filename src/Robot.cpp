#include "Robot.h"

Robot::Robot(int startX, int startY)
    : posX(startX), posY(startY), direction(0) {}

int Robot::getX() const {
    return posX;
}

int Robot::getY() const {
    return posY;
}
