#include<iostream>
#include<list>


class Neurona{

    private:
        int id;
        float voltaje;
        int posicion_x;
        int posicion_y;
        int red;
        int green;
        int blue;
    public:
        void setId(int& id){id = id;};
        void setVoltaje(int& vol){voltaje = vol;};
        void setPosicion_x(int& x){posicion_x = x;};
        void setPosicion_y(int& y){posicion_y = y;};
        void setRed(int& rojo){red = rojo;};
        void setGreen(int& verde){green = verde;};
        void setBlue(int& azul){blue = azul;};

        int getId(){return id;};
        float getVoltaje(){return voltaje;};
        int getPosicion_x(){return posicion_x;};
        int getPosicion_y(){return posicion_y;};
        int getRed(){return red;};
        int getGreen(){return green;};
        int getBlue(){return blue;};

       void print() {
        std::cout << "Neurona #" << id << "\n";
        std::cout << "Voltaje: " << voltaje << "\n";
        std::cout << "Posición X: " << posicion_x << "\n";
        std::cout << "Posición Y: " << posicion_y << "\n";
        std::cout << "Color RGB: (" << red << ", " << green << ", " << blue << ")\n";
    }
        
};


class AdministradorNeuronas {
private:
    std::list<Neurona> listaNeuronas;  

public:
    void agregarInicio(const Neurona& neurona) {
        listaNeuronas.push_front(neurona);
    }

    void agregarFinal(const Neurona& neurona) {
        listaNeuronas.push_back(neurona);
    }

    void mostrar() {
        for (const auto& neurona : listaNeuronas) {
            Neurona.print();
            std::cout << "---------------------\n";
        }
    }
};