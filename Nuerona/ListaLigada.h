#ifndef LISTALIGADA_H
#define LISTALIGADA_H
#include <iostream>
#include <fstream>
#include <string>
#include"Neron.h"

template<class T>
class node{
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
node<T>::node(){sig = nullptr;}


template<class T>
node<T>::node(const T& dat){
    data  = dat;
    sig  = nullptr;
}


template<class T>
void node<T>::setData(const T& dat){
    data = dat;
}

template<class T>
void node<T>::setSiguiente(node<T>* pos){
    sig = pos;
}

template<class T>
T node<T>::getData(){
    return data;
}

template<class T>
node<T>* node<T>::getSiguiente(){
    return sig;
}

template<class T>
class LSLSE{
private:
    node<T>* header;
public:
    LSLSE():header(nullptr){};
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
bool LSLSE<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==header){
        header=header->getSiguiente();
    }
    else{
        anterior(pos)->setSiguiente(pos->getSiguiente());
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertarInicio(T elem){
    node<T>* aux(new node<T>(elem));

    if(aux == nullptr){
        std::cout<<"Memoria insuficiente\n";
        return;
    }

    aux->setSiguiente(header);
    header = aux;
}

template<class T>
void LSLSE<T>::insertarFinal(T elem){
    node<T>* aux(new node<T>(elem));

    if(aux == nullptr){
        std::cout<<"Memoria insuficiente\n";
        return;
    }

    if(vacia()){
        header = aux;
    } else {
        node<T>* ultimoNodo = ultimo();
        ultimoNodo->setSiguiente(aux);
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=header;
    while(aux!=nullptr && aux->getSiguiente()!=pos){
        aux=aux->getSiguiente();
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return header;
}


template<class T>
node<T>* LSLSE<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=header;
    while(aux->getSiguiente()!=nullptr){
        aux=aux->getSiguiente();
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia()const{
    if(header==nullptr)
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
        Neurona neurona(0,0,0,0,0,0,0);
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
void LSLSE<T>::guardarDatos(){

    node<Neurona>* aux= header;

    std::ofstream archivoNeuronas;
    archivoNeuronas.open("Neuronas.txt", std::ios::out);

    while (aux!=nullptr){
        Neurona neu(0,0,0,0,0,0,0);
        neu= aux->getData();

        archivoNeuronas<<neu.getId()<<" "<<neu.getVoltaje()<<" "<<neu.getPosicion_x()<<" "<<neu.getPosicion_y()<<" "<<neu.getRed()<<" "<<neu.getBlue()<<" "<<neu.getGreen()<<std::endl;

        aux = aux->getSiguiente();
    }

    archivoNeuronas.close();

}

template<class T>
node<T>* LSLSE<T>::Buscar(int& obj){
    Neurona elm(0,0,0,0,0,0,0);
    elm.setId(obj);

    node<T>* aux = header;
    while(aux != nullptr && aux->getData() != elm){
        aux = aux->getSiguiente();
    }
    return aux;
}


#endif // LISTALIGADA_H
