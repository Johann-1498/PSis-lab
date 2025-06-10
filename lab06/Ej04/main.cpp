#include "lector.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string nombreArchivo;
    cout << "Introduce el nombre del archivo a leer: ";
    getline(cin, nombreArchivo);

    mostrarArchivoPorBloques(nombreArchivo);

    return 0;
}
