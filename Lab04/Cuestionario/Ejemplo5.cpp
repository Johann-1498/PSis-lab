#include <iostream>
#include <memory>
using namespace std;

class Imagen {
public:
    void mostrar() { cout << "Mostrar imagen" << endl; }
};

int main() {
    shared_ptr<Imagen> img1 = make_shared<Imagen>();
    shared_ptr<Imagen> img2 = img1;  // Un mismo recurso
    shared_ptr<Imagen> img3 = img1;  // Un mismo recurso

    img1->mostrar();
    cout << "Cantidad de punteros activos: " << img1.use_count() << endl;

    return 0;
}
