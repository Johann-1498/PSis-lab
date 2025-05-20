#include <iostream>
#include <memory>
using namespace std;

bool verificarPuntoSilla(unique_ptr<unique_ptr<double[]>[]>& matriz, int filas, int columnas, int fila, int columna) {
    double* pFila = matriz[fila].get();         // inicio de la fila actual
    double valor = *(pFila + columna);          // valor del elemento actual (fila, columna)

    // Verificar si es el mínimo en su fila
    for (double* pElemento = pFila; pElemento < pFila + columnas; ++pElemento) {
        if (*pElemento < valor)
            return false;
    }

    // Verificar si es el máximo en su columna
    for (int i = 0; i < filas; ++i) {
        double* pColumna = matriz[i].get() + columna;  // pColumna apunta al elemento en la columna específica
        if (*pColumna > valor)
            return false;
    }

    return true;
}

// Buscar punto silla usando punteros
void buscarPuntoSilla(unique_ptr<unique_ptr<double[]>[]>& matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        double* pFila = matriz[i].get();  // pFila apunta al inicio de la fila actual
        for (int j = 0; j < columnas; ++j) {
            if (verificarPuntoSilla(matriz, filas, columnas, i, j)) {
                cout << "Punto de silla encontrado en (" << i + 1 << ", " << j + 1
                     << ") con valor: " << *(pFila + j) << endl;
                return;
            }
        }
    }
    cout << "No se encontro ningun punto de silla en la matriz." << endl;
}

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

    // Matriz punteros inteligentes
    unique_ptr<unique_ptr<double[]>[]> matriz(new unique_ptr<double[]>[filas]);
    for (int i = 0; i < filas; ++i) {
        matriz[i] = unique_ptr<double[]>(new double[columnas]);
    }

    //-------------------------------------------------------
    cout << "Ingrese los elementos de la matriz:" << endl;
    for (int i = 0; i < filas; ++i) {
        double* pFila = matriz[i].get();  // pFila apunta al inicio de la fila actual
        for (int j = 0; j < columnas; ++j) {
            cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> *(pFila + j);          // acceso usando aritmética de punteros
        }
    }

    // Buscar punto silla
    buscarPuntoSilla(matriz, filas, columnas);
    return 0;
}
