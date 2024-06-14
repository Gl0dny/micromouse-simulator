#include "Sensor.h"

template <typename T>
Sensor<T>::Sensor() : data(T()) {}

template <typename T>
T Sensor<T>::getReading(int direction) const {
    // Return sensor reading for the given direction
    return data;
}

// To ensure template class is instantiated correctly
template class Sensor<int>;
template class Sensor<float>;
template class Sensor<double>;

