#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Poligono {
public:
    virtual void mostrarLados() {
        cout << "Poligono: tiene entre 3 a mas lados" << endl;
    }
    virtual ~Poligono() {}
};

class Triangulo : public Poligono {
public:
    void mostrarLados() override {
        cout << "Triangulo: 3 lados" << endl;
    }
};

class Cuadrado : public Poligono {
public:
    void mostrarLados() override {
        cout << "Cuadrado: 4 lados" << endl;
    }
};

int main() {
    vector<Poligono*> poligonos;
    poligonos.push_back(new Cuadrado());
    poligonos.push_back(new Triangulo());
    poligonos.push_back(new Cuadrado());
    poligonos.push_back(new Cuadrado());
    poligonos.push_back(new Triangulo());


    for (const auto& figura : poligonos)
        figura->mostrarLados();

    return 0;
}
