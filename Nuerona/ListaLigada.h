#ifndef LISTALIGADA_H
#define LISTALIGADA_H

#include <iostream>
#include <fstream>
#include <string>
#include "Neron.h"
#include <cmath>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>


template<class T>
class node {
private:
    T data;
    node<T>* sig;

public:
    node();
    node(const T&);

    void setData(const T&);
    void setSiguiente(node<T>*);

    T getData();
    node<T>* getSiguiente();
};

template<class T >
node<T>::node() { sig = nullptr; }


template<class T>
node<T>::node(const T& dat) {
    data = dat;
    sig = nullptr;
}


template<class T>
void node<T>::setData(const T& dat) {
    data = dat;
}

template<class T>
void node<T>::setSiguiente(node<T>* pos) {
    sig = pos;
}

template<class T>
T node<T>::getData() {
    return data;
}

template<class T>
node<T>* node<T>::getSiguiente() {
    return sig;
}

template<class T>
class LSLSE {
private:
    node<T>* header;
    std::vector<std::vector<int>> adyacencia;
    int contador;
public:

    LSLSE() :header(nullptr) {};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertarInicio(T elem);
    void insertarFinal(T elem);
    bool eliminar(node<T>* pos);
    std::string imprimir()const;

    void cargarDatos(const std::string& nombreArchivo);
    void guardarDatos();
    std::string toString()const;

    node<T>* Buscar(int&);
    void swap(node<T>*, node<T>*);
    void Ordenamiento_id();
    void Ordenamiento_voltaje();
    void calcularDistancias(QGraphicsScene& scene);

    void construirListaAdyacencia();
    void imprimirListaAdyacencia(std::string&) const;
    void reasignarIDs();

    node<T>* encontrarNodoConIdMasPequeno() const;

    void recorrido_profundidad(int startId, std::string& resultadoDFS);
    void recorrid_amplitud(int startId, std::string& resultadoBFS);
    void imprimirProfundidad(int startId, std::string& dfsStr);
    void imprimirAmplitud(int startId, std::string& bfsStr);

};

template<class T>
std::string LSLSE<T>::toString() const {
    std::string result;
    node<T>* aux = header;
    while (aux != nullptr) {
        result += aux->getData().toString_neurona() + "-> ";
        aux = aux->getSiguiente();
    }
    return result;
}


template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == header) {
        header = header->getSiguiente();
    }
    else {
        anterior(pos)->setSiguiente(pos->getSiguiente());
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertarInicio(T elem) {
    node<T>* aux(new node<T>(elem));

    if (aux == nullptr) {
        std::cout << "Memoria insuficiente\n";
        return;
    }

    aux->setSiguiente(header);
    header = aux;
}

template<class T>
void LSLSE<T>::insertarFinal(T elem) {
    node<T>* aux(new node<T>(elem));

    if (aux == nullptr) {
        std::cout << "Memoria insuficiente\n";
        return;
    }

    if (vacia()) {
        header = aux;
    }
    else {
        node<T>* ultimoNodo = ultimo();
        ultimoNodo->setSiguiente(aux);
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos) const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T>* aux = header;
    while (aux != nullptr && aux->getSiguiente() != pos) {
        aux = aux->getSiguiente();
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero() const {
    if (vacia()) {
        return nullptr;
    }
    return header;
}


template<class T>
node<T>* LSLSE<T>::ultimo() const {
    if (vacia()) {
        return nullptr;
    }
    node<T>* aux = header;
    while (aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia() const {
    if (header == nullptr)
        return true;
    return false;
}

template<class T>
void LSLSE<T>::cargarDatos(const std::string& nombreArchivo) {

    std::ifstream archivoEntrada(nombreArchivo, std::ios::in);
    int id, posicion_x, posicion_y, red, green, blue;
    float voltaje;

    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo \n";
        return;
    }

    while (archivoEntrada >> id >> voltaje >> posicion_x >> posicion_y >> red >> green >> blue) {
        Neurona neurona(0, 0, 0, 0, 0, 0, 0);
        neurona.setId(id);
        neurona.setVoltaje(voltaje);
        neurona.setPosicion_x(posicion_x);
        neurona.setPosicion_y(posicion_y);
        neurona.setRed(red);
        neurona.setGreen(green);
        neurona.setBlue(blue);

        insertarFinal(neurona);
    }

    archivoEntrada.close();
}


template<class T>
void LSLSE<T>::guardarDatos() {

    node<Neurona>* aux = header;

    std::ofstream archivoNeuronas;
    archivoNeuronas.open("Neuronas.txt", std::ios::out);

    while (aux != nullptr) {
        Neurona neu(0, 0, 0, 0, 0, 0, 0);
        neu = aux->getData();

        archivoNeuronas << neu.getId() << " " << neu.getVoltaje() << " " << neu.getPosicion_x() << " " << neu.getPosicion_y() << " " << neu.getRed() << " " << neu.getBlue() << " " << neu.getGreen() << std::endl;

        aux = aux->getSiguiente();
    }

    archivoNeuronas.close();

}

template<class T>
node<T>* LSLSE<T>::Buscar(int& obj) {
    Neurona elm(0, 0, 0, 0, 0, 0, 0);
    elm.setId(obj);

    node<T>* aux = header;
    while (aux != nullptr && aux->getData() != elm) {
        aux = aux->getSiguiente();
    }
    return aux;
}


template<class T>
void LSLSE<T>::swap(node<T>* a, node<T>* b) {
    T temp = a->getData();
    a->setData(b->getData());
    b->setData(temp);
}


template<class T>
void LSLSE<T>::Ordenamiento_id() {
    bool flag = true;
    while (flag) {
        flag = false;
        node<T>* actual = header;
        node<T>* siguiente = header->getSiguiente();

        while (siguiente != nullptr) {
            if (actual->getData() > siguiente->getData()) {
                swap(actual, siguiente);
                flag = true;
            }
            actual = siguiente;
            siguiente = siguiente->getSiguiente();
        }
    }
}

template<class T>
void LSLSE<T>::Ordenamiento_voltaje() {
    bool flag = true;
    while (flag) {
        flag = false;
        node<T>* actual = header;
        node<T>* siguiente = header->getSiguiente();

        while (siguiente != nullptr) {
            if (actual->getData().getVoltaje() > siguiente->getData().getVoltaje()) {
                swap(actual, siguiente);
                flag = true;
            }
            actual = siguiente;
            siguiente = siguiente->getSiguiente();
        }
    }
}

template<class T>
void LSLSE<T>::calcularDistancias(QGraphicsScene& scene) {
    node<T>* actual = header;

    while (actual != nullptr) {
        node<T>* otraNeurona = header;
        float menorDistancia = std::numeric_limits<float>::max(); // Inicializar con un valor grande
        node<T>* neuronaCercana = nullptr;

        while (otraNeurona != nullptr) {
            if (otraNeurona != actual) {
                float x1 = actual->getData().getPosicion_x() + actual->getData().getVoltaje() / 2;
                float y1 = actual->getData().getPosicion_y() + actual->getData().getVoltaje() / 2;
                float x2 = otraNeurona->getData().getPosicion_x() + otraNeurona->getData().getVoltaje() / 2;
                float y2 = otraNeurona->getData().getPosicion_y() + otraNeurona->getData().getVoltaje() / 2;

                float distancia = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    neuronaCercana = otraNeurona;
                }
            }

            otraNeurona = otraNeurona->getSiguiente();
        }

        if (neuronaCercana != nullptr) {
            float x1 = actual->getData().getPosicion_x() + actual->getData().getVoltaje() / 2;
            float y1 = actual->getData().getPosicion_y() + actual->getData().getVoltaje() / 2;
            float x2 = neuronaCercana->getData().getPosicion_x() + neuronaCercana->getData().getVoltaje() / 2;
            float y2 = neuronaCercana->getData().getPosicion_y() + neuronaCercana->getData().getVoltaje() / 2;


            QGraphicsLineItem* line = scene.addLine(x1, y1, x2, y2);


            float midX = (x1 + x2) / 2;
            float midY = (y1 + y2) / 2;

            QGraphicsTextItem* idText = scene.addText(QString::number(actual->getData().getId()));
            idText->setPos(midX-20, midY);


            QGraphicsSimpleTextItem* distanceText = scene.addSimpleText(QString::number(menorDistancia));
            distanceText->setPos(midX, midY);

            QPen pen(Qt::black);
            pen.setWidth(2);
            line->setPen(pen);
        }

        actual = actual->getSiguiente();
    }
}


template<class T>
void LSLSE<T>::construirListaAdyacencia() {
    adyacencia.resize(100);
    for (size_t i = 0; i < 100; i++) {
        adyacencia[i].resize(100);
        for (size_t j = 0; j < 100; j++) {
            adyacencia[i][j] = 0;
        }
    }

    node<T>* actual = header;

    while (actual != nullptr) {
        node<T>* otraNeurona = header;
        float menorDistancia = std::numeric_limits<float>::max();
        node<T>* neuronaCercana = nullptr;

        while (otraNeurona != nullptr) {
            if (otraNeurona != actual) {
                float x1 = actual->getData().getPosicion_x();
                float y1 = actual->getData().getPosicion_y();
                float x2 = otraNeurona->getData().getPosicion_x();
                float y2 = otraNeurona->getData().getPosicion_y();

                float distancia = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    neuronaCercana = otraNeurona;
                }
            }

            otraNeurona = otraNeurona->getSiguiente();
        }

        if (neuronaCercana != nullptr) {
            int id1 = actual->getData().getId();
            int id2 = neuronaCercana->getData().getId();
            adyacencia[id1][id2] = 1;
            std::cout << "Conectando nodo " << id1 << " con nodo " << id2 << std::endl; // Imprimir conexiones
        }

        actual = actual->getSiguiente();
    }
}


template<class T>
void LSLSE<T>::imprimirListaAdyacencia(std::string& listaAdyacenciaStr) const {
    listaAdyacenciaStr = "";
    for (size_t i = 0; i < adyacencia.size(); i++) {
        listaAdyacenciaStr += "Nodo " + std::to_string(i) + "-> ";
        for (size_t j = 0; j < adyacencia[i].size(); j++) {
            if (adyacencia[i][j] == 1) {
                listaAdyacenciaStr += std::to_string(j) + " ";
            }
        }
        listaAdyacenciaStr += "\n";
    }
}


template<class T>
void LSLSE<T>::reasignarIDs() {
    int id = 0;
    node<T>* actual = header;

    while (actual != nullptr) {
        actual->getData().setId(id++);
        actual = actual->getSiguiente();
    }
}

template<class T>
node<T>* LSLSE<T>::encontrarNodoConIdMasPequeno() const {
    if (vacia()) return nullptr;

    node<T>* actual = header;
    node<T>* nodoConIdMasPequeno = actual;

    while (actual != nullptr) {
        if (actual->getData().getId() < nodoConIdMasPequeno->getData().getId()) {
            nodoConIdMasPequeno = actual;
        }
        actual = actual->getSiguiente();
    }

    return nodoConIdMasPequeno;
}


template<class T>
void LSLSE<T>::recorrido_profundidad(int startId, std::string& resultadoDFS) {
    std::stack<int> stack;
    std::unordered_set<int> visitados;

    stack.push(startId);
    visitados.insert(startId);

    while (!stack.empty()) {
        int id = stack.top();
        stack.pop();
        resultadoDFS += std::to_string(id) + " ";

        for (int i = adyacencia[id].size() - 1; i >= 0; --i) {
            if (adyacencia[id][i] == 1 && visitados.find(i) == visitados.end()) {
                stack.push(i);
                visitados.insert(i);
            }
        }
    }
}

// Implementación del método BFS
template<class T>
void LSLSE<T>::recorrid_amplitud(int startId, std::string& resultadoBFS) {
    std::queue<int> queue;
    std::unordered_set<int> visitados;

    queue.push(startId);
    visitados.insert(startId);

    while (!queue.empty()) {
        int id = queue.front();
        queue.pop();
        resultadoBFS += std::to_string(id) + " ";

        for (size_t i = 0; i < adyacencia[id].size(); ++i) {
            if (adyacencia[id][i] == 1 && visitados.find(i) == visitados.end()) {
                queue.push(i);
                visitados.insert(i);
            }
        }
    }
}

// Implementación de la función de impresión de DFS
template<class T>
void LSLSE<T>::imprimirProfundidad(int startId, std::string& dfsStr) {
    std::string resultadoDFS;
    recorrido_profundidad(startId, resultadoDFS);
    dfsStr = "Recorrido DFS desde nodo " + std::to_string(startId) + ": " + resultadoDFS + "\n";
}

// Implementación de la función de impresión de BFS
template<class T>
void LSLSE<T>::imprimirAmplitud(int startId, std::string& bfsStr) {
    std::string resultadoBFS;
    recorrid_amplitud(startId, resultadoBFS);
    bfsStr = "Recorrido BFS desde nodo " + std::to_string(startId) + ": " + resultadoBFS + "\n";
}



#endif // LISTALIGADA_H
