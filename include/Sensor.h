#ifndef SENSOR_H
#define SENSOR_H

template <typename T>
class Sensor {
public:
    Sensor();
    T getReading(int direction) const;

private:
    T data;
};

#endif // SENSOR_H

// Kod deklaruje klasę Sensor, która może przechowywać i zwracać dane różnych typów.
// Template class jest instancjonowany dla konkretnych typów danych na końcu pliku implementacyjnego, aby zapewnić, że będą one gotowe do użycia w programie.