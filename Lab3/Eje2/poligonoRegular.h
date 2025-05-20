// PoligonoRegular.h
#ifndef POLIGONOREGULAR_H
#define POLIGONOREGULAR_H
#include "Poligono.h"
class PoligonoRegular : public Poligono {
public:
    PoligonoRegular(int numl, double longl)
      : numLados(numl), longLados(longl) {}

    double area() const override;
    double perimetro() const override;
    void print() const override;

private:
    int    numLados;
    double longLados;
};

#endif 
