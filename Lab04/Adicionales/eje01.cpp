#include <iostream>
#include <iomanip>

using namespace std;

void imprimirTrianguloPascal(int niveles) {
    // Crear un arreglo unidimensional lo suficientemente grande
    int* triangulo = new int[niveles * (niveles + 1) / 2];
    
    int pos = 0; // Posición actual en el arreglo
    
    for (int fila = 0; fila < niveles; fila++) {
        // Calcular los valores de la fila actual
        for (int col = 0; col <= fila; col++) {
            if (col == 0 || col == fila) {
                triangulo[pos + col] = 1; // Los bordes son siempre 1
            } else {
                // Calcular la posición del elemento de la fila anterior
                int posAnterior = pos - fila;
                // El valor es la suma de los dos elementos encima de él
                triangulo[pos + col] = triangulo[posAnterior + col - 1] + triangulo[posAnterior + col];
            }
        }
        
        // Imprimir espacios para centrar la fila
        cout << setw((niveles - fila) * 2) << "";
        
        // Imprimir los valores de la fila actual
        for (int col = 0; col <= fila; col++) {
            cout << setw(4) << triangulo[pos + col];
        }
        cout << endl;
        
        // Actualizar la posición para la siguiente fila
        pos += fila + 1;
    }
    
    delete[] triangulo;
}

int main() {
    int niveles;
    cout << "Ingrese el numero de niveles del triangulo de Pascal: ";
    cin >> niveles;
    
    imprimirTrianguloPascal(niveles);
    
    return 0;
}
