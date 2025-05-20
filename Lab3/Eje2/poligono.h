#ifndef POLIGONO_H
#define POLIGONO_H

#include <iostream>

class Poligono {
protected:
    int numLados;
    int area;
    int longLado;
public:
    Poligono(int l){
        numLados = l;
    }
    // virtual es para que se puede hacer polimorfismo en otras clases hijas
    virtual void print();
    virtual double calcularPerimetro();
    virtual double calcularArea();
};
#endif