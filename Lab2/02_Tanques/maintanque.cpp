#include "tanque.h"
#include <iostream>
using namespace std;

int main() {
    Tanque tanq;

    tanq.agregar(100); 
    cout << "Tanque 1 contiene " << tanq.getContenido() << endl;

    while (tanq.getContenido() >= 1.0) {
        tanq.sacaMitad();
        cout << "Tanque 1, despues de sacar la mitad, contiene: " << tanq.getContenido() << endl;
    }

    return 0;
}
