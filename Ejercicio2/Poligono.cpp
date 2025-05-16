#include "Poligono.h"
#include <cmath>     // std::tan, std::abs

static constexpr double PI = 3.14159265358979323846;

// ----- PoligonoRegular -------------------------------------
PoligonoRegular::PoligonoRegular(int n_, double lado_)
    : n(n_), lado(lado_) {}

double PoligonoRegular::area() const {
    return (n * lado * lado) / (4.0 * std::tan(PI / n));
}

// ----- PoligonoIrregular -----------------------------------
PoligonoIrregular::PoligonoIrregular(const std::vector<Punto>& v_)
    : v(v_) {}

double PoligonoIrregular::area() const {
    double suma = 0.0;
    int m = static_cast<int>(v.size());
    for (int i = 0; i < m; ++i) {
        const Punto& p1 = v[i];
        const Punto& p2 = v[(i + 1) % m];
        suma += (p1.x * p2.y) - (p2.x * p1.y);
    }
    return std::abs(suma) * 0.5;
}
