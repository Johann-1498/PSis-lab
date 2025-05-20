#include <iostream>
#include <memory>
using namespace std;

class Libro {
public:
    void leer() { cout << "Leyendo libro" << endl; }
};

int main() {
    unique_ptr<Libro> libro = make_unique<Libro>();
    libro->leer();  // se accede como un puntero normal
    return 0;
}
