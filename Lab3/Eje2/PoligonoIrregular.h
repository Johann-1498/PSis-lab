#include "Poligono.h"

class PoligonoIrregular : public Poligono {
private:
    Punto* coordenadas;   // arreglo de puntos
public:
    PoligonoIrregular(Punto* p);
    void calcularArea() override;
    int getLados();
    void print() override;
};