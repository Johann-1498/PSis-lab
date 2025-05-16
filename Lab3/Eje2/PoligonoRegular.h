#include "Poligono.h"
#include <cmath>

static constexpr double PI = 3.14159265358979323846;

class PoligonoRegular : public Poligono {
private:
    double longLado;

public:
    PoligonoRegular(int lados, double longitud);
    void calcularArea() override;
    void print() const override;
};

