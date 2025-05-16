#include "Poligono.h"

class PoligonoRegular : public Poligono {
private:
    double longLado;//Todos los poligonos regulares tienen los lados iguales
public:
    PoligonoRegular(int lados, double longitud);
    void calcularArea() ;
    void print() ;
};