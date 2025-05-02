// persona.cpp
#include "persona.h"
#include <iostream>
#include <cstring>
using namespace std;

void Persona::dormir() {
    cout << nombre << " esta durmiendo" << endl;
}

void Persona::hablar() {
    cout << nombre << " esta hablando" << endl;
}

void Persona::contar() {
    cout << nombre << " esta contando" << endl;
}

void Persona::adquirirNombre() {
    cout << "Ingrese el nombre: ";
    cin.getline(nombre, 50);
}

void Persona::decirNombre() {
    cout << "Mi nombre es: " << nombre << endl;
}
