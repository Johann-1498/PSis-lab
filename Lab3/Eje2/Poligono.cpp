#include "Poligono.h"
#include <iostream>

void Poligono::print() const {
    std::cout <<"Poligono de area: "<< getArea() <<"\n";
}

double Poligono::getArea() const {
    return area;
}

int Poligono::getNumLados() const {
    return static_cast<int>(numLados);
}
