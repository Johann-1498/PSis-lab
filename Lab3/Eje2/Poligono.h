class Poligono {
protected:
    double area;
    double numLados;

public:
    Poligono();                      
    virtual void calcularArea() = 0; // Método puro virtual
    virtual void print();         
    double getArea(); 
    virtual int getNumLados();
};
struct Punto { double x,y; };
