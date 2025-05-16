#include "PoligonoIrregular.h"
#include <iostream>
#include <cmath>

PoligonoIrregular::PoligonoIrregular(std::vector<Punto>& coordenadas)
    : coordenadas(coordenadas)
{
    numLados = static_cast<double>(coordenadas.size());
    area      = 0.0;
}

void PoligonoIrregular::calcularArea() {
    double suma = 0.0;
    int m = static_cast<int>(coordenadas.size());
    if (m < 3) {
        area = 0.0;
        return;
    }
    for (int i = 0; i < m; ++i) {
        const Punto& p1 = coordenadas[i];
        const Punto& p2 = coordenadas[(i + 1) % m];
        suma += p1.x * p2.y - p2.x * p1.y;
    }
    area = std::abs(suma) * 0.5;
}

void PoligonoIrregular::print() const {
    std::cout
        << "---------POLIGONO IRREGULAR------------------\n"
        << "- Numero de Lados : " << getNumLados() << "\n"
        << "- Area : " << getArea() << "\n";
}
