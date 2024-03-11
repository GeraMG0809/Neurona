#ifndef NEURONA_H
#define NEURONA_H

#include <iostream>
#include <string>

class Neurona {
private:
    int id;
    float voltaje;
    int posicion_x;
    int posicion_y;
    int red;
    int green;
    int blue;

public:
    Neurona() : id(0), voltaje(0.0), posicion_x(0), posicion_y(0), red(0), green(0), blue(0) {}

    Neurona(int i, float v, int x, int y, int r, int g, int b) : id(i), voltaje(v), posicion_x(x), posicion_y(y), red(r), green(g), blue(b) {}

    void setId(int i) { id = i; }
    void setVoltaje(float vol) { voltaje = vol; }
    void setPosicion_x(int x) { posicion_x = x; }
    void setPosicion_y(int y) { posicion_y = y; }
    void setRed(int rojo) { red = rojo; }
    void setGreen(int verde) { green = verde; }
    void setBlue(int azul) { blue = azul; }

    int getId() const { return id; }
    float getVoltaje() const { return voltaje; }
    int getPosicion_x() const { return posicion_x; }
    int getPosicion_y() const { return posicion_y; }
    int getRed() const { return red; }
    int getGreen() const { return green; }
    int getBlue() const { return blue; }

    void print() const {
        std::cout << "Neurona #" << id << "\n";
        std::cout << "Voltaje: " << voltaje << "\n";
        std::cout << "Posición X: " << posicion_x << "\n";
        std::cout << "Posición Y: " << posicion_y << "\n";
        std::cout << "Color RGB: (" << red << ", " << green << ", " << blue << ")\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Neurona& neurona) {
        os << "Neurona #" << neurona.getId() << "\n";
        os << "Voltaje: " << neurona.getVoltaje() << "\n";
        os << "Posición X: " << neurona.getPosicion_x() << "\n";
        os << "Posición Y: " << neurona.getPosicion_y() << "\n";
        os << "Color RGB: (" << neurona.getRed() << ", " << neurona.getGreen() << ", " << neurona.getBlue() << ")\n";
        return os;
    }

    std::string toString_neurona() const {
        std::string result = "Neurona #" + std::to_string(id) + "\n";
        result += "Voltaje: " + std::to_string(voltaje) + "\n";
        result += "Posición X: " + std::to_string(posicion_x) + "\n";
        result += "Posición Y: " + std::to_string(posicion_y) + "\n";
        result += "Color RGB: (" + std::to_string(red) + ", " + std::to_string(green) + ", " + std::to_string(blue) + ")\n";
        return result;
    }

    friend bool operator<(const Neurona& n1, const Neurona& n2) {
        return n1.getId() < n2.getId();
    }

    friend bool operator>(const Neurona& n1, const Neurona& n2) {
        return n1.getId() > n2.getId();
    }

    friend bool operator==(const Neurona& n1, const Neurona& n2) {
        return n1.getId() == n2.getId();
    }

    friend bool operator!=(const Neurona& n1, const Neurona& n2) {
        return n1.getId() != n2.getId();
    }
};

#endif // NEURONA_H
