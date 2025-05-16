#ifndef POLIGONOIRREGULAR_H
#define POLIGONOIRREGULAR_H
#include "Poligono.h"
#include "Punto.h"
#include <Vector>
class PoligonoIrregular : public Poligono {
private:
    std::vector<Punto> coordenadas;
public:
    PoligonoIrregular(std::vector<Punto>& coordenadas);
    void calcularArea() override;
    int getLados();
    void print() const override;
};
#endif 

