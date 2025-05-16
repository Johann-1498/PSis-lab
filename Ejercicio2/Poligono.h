#include <vector>

class Poligono{
public:
    double area;
public:    
    virtual double calcularArea()=0; 
};

class PoligonoRegular : public Poligono{
private:
    int lados;
    double longitud;
public:
    PoligonoRegular(int lados, double longitud);
    double calcularArea() override;
};

class PoligonoIrregular : public Poligono{
public:
  std::vector<Punto> vertice;   
public:
    PoligonoIrregular(std::vector<Punto> vertices);
    double calcularArea() override;
};

class Punto{
public:
    double x, y;
    Punto(double x,double y);
};