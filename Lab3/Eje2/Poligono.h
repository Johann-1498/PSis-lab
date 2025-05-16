#ifndef POLIGONO_H
#define POLIGONO_H
#include <vector>

struct Punto;

class Poligono {
protected:
    double area;
    double numLados;

public:
    Poligono() = default;
    virtual ~Poligono() = default;

    virtual void calcularArea() = 0;  
    virtual void print() const;        

    double getArea() const;            
    virtual int getNumLados() const;  
};

#endif