#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehiculo {
public:
    virtual void describir() {
        cout << "Este es un vehículo." << endl;
    }
    virtual ~Vehiculo() {}
};

class Tractor : public Vehiculo {
public:
    void describir() override {
        cout << "Soy un tractor" << endl;
    }
};

class Bote : public Vehiculo {
public:
    void describir() override {
        cout << "Soy un bote" << endl;
    }
};

class Auto : public Vehiculo {
public:
    void describir() override {
        cout << "Soy un auto" << endl;
    }
};

int main() {
    vector<unique_ptr<Vehiculo>> vehiculos;
    vehiculos.push_back(make_unique<Tractor>());
    vehiculos.push_back(make_unique<Bote>());
    vehiculos.push_back(make_unique<Auto>());
    vehiculos.push_back(make_unique<Auto>());
    vehiculos.push_back(make_unique<Auto>());
    vehiculos.push_back(make_unique<Auto>());

    for (const auto& v : vehiculos)
        v->describir();

    return 0;
}
