#ifndef POLIGONO_H
#define POLIGONO_H

#include <iostream>
#include <vector>
#include <cmath>

// Clase base
class PoligonoRegular {
protected:
    int numLados;
    int area;
    int perimetro;
public:
    PoligonoRegular(int l){
        numLados = l;
    }
    // virtual es para que se puede hacer polimorfismo en otras clases hijas
    virtual void print();
    virtual double calcularPerimetro();
    virtual double area();

};
#endif