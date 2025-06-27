#include <iostream>
#include <new> // Para std::bad_alloc
using namespace std;

int main() {
    try {
        // Intentamos asignar una cantidad enorme de memoria
        int* arreglo = new int[1000000000000];
        cout << "Memoria asignada correctamente." << endl;
        delete[] arreglo;
    } catch (const bad_alloc& e) {
        cout << "Error: No se pudo asignar memoria. " << e.what() << endl;
    }
    return 0;
}
