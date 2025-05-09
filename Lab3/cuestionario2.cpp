#include <iostream>
using namespace std;

// Sobrecarga de funciones
void imprimir(int i) {
    cout << "Entero: " << i << endl;
}

void imprimir(double d) {
    cout << "Double: " << d << endl;
}

void imprimir(const char* s) {
    cout << "Cadena: " << s << endl;
}

int main() {
    imprimir(5);       // Llama a imprimir(int)
    imprimir(3.14);    // Llama a imprimir(double)
    imprimir("Hola");  // Llama a imprimir(const char*)
    
    return 0;
}
