#include <iostream>
#include <memory>
using namespace std;

bool verificarPuntoSilla(unique_ptr<unique_ptr<double[]>[]>& matriz, int filas, int columnas, int fila, int columna) {
    double* pFila = matriz[fila].get();  //matriz[fila]
    double valor = *(pFila + columna);   // pFila[columna]

    // Menor de su fila
    for (int j = 0; j < columnas; ++j) {
        if (*(pFila + j) < valor) {
            return false;  
        }
    }
    // si hay uno mayor
    for (int i = 0; i < filas; ++i) {
        double* pColumna = matriz[i].get();  // puntero a fila i
        if (*(pColumna + columna) > valor) {
            return false;  
        }
    }

    return true;
}

void buscarPuntoSilla(unique_ptr<unique_ptr<double[]>[]>& matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        double* pFila = matriz[i].get();
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

void llenarMatriz(unique_ptr<unique_ptr<double[]>[]>& matriz, int filas, int columnas) {
    cout << "Ingrese los elementos de la matriz:" << endl;
    for (int i = 0; i < filas; ++i) {
        double* pFila = matriz[i].get();
        for (int j = 0; j < columnas; ++j) {
            cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> *(pFila + j);
        }
    }
}

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

    // matriz bidimencinal con punteros inteligentes unicos
    unique_ptr<unique_ptr<double[]>[]> matriz(new unique_ptr<double[]>[filas]);
    for (int i = 0; i < filas; ++i) {
        matriz[i] = unique_ptr<double[]>(new double[columnas]);
    }

    llenarMatriz(matriz, filas, columnas);
    buscarPuntoSilla(matriz, filas, columnas);

    return 0;
}