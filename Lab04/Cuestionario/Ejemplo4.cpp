#include <iostream>
#include <memory>
using namespace std;

class Conexion {
public:
    void estado() { cout << "Activo" << endl; }
};

int main() {
    shared_ptr<Conexion> red = make_shared<Conexion>();
    weak_ptr<Conexion> referencia = red;

    if (auto c = referencia.lock()) {
        c->estado();  // Funcionara siempre y cuadno exista red
    } else {
        cout << "No disponible" << endl;
    }

    return 0;
}
