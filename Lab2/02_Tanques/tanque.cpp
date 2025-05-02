#include "tanque.h"
#include <iostream>
using namespace std;

//
double Tanque::getContenido() const {
    return contenido;
}

void Tanque::agregar(double cantidad) {
    if (contenido + cantidad <= capacidad) {
        contenido += cantidad;
    }
}

void Tanque::sacar(double cantidad) {
    if (cantidad <= contenido) {
        contenido -= cantidad;//Resta la cantidad que se esta sacando
    } else {
        contenido = 0;//Si es mayor a lo disponible sacará del tanque todo lo que puede pero si la cantidad se pasa no sacara mas de lo que hay disponible
    }
}

void Tanque::sacaMitad() {
    if (contenido > 0) {//Se asegura que el tanque no este vacio
        contenido /= 2;//Divide en dos la cantidad disponible en el tanque
    }
}
