#ifndef POLIGONO_H
#define POLIGONO_H

#include <vector>

// --- Punto -------------------------------------------------
struct Punto {
    double x, y;
    Punto(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

// --- Clase base (abstracta) --------------------------------
class Poligono {
public:
    virtual double area() const = 0;   // método puro
    virtual ~Poligono() = default;
};

// --- Polígono regular --------------------------------------
class PoligonoRegular : public Poligono {
    int    n;       // nº de lados
    double lado;    // longitud del lado
public:
    PoligonoRegular(int n_, double lado_);
    double area() const override;
};

// --- Polígono irregular ------------------------------------
class PoligonoIrregular : public Poligono {
    std::vector<Punto> v;   // vértices
public:
    explicit PoligonoIrregular(const std::vector<Punto>& v_);
    double area() const override;
};

#endif // POLIGONO_H
