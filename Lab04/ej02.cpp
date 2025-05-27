#include <iostream>
using namespace std;

bool verificarPuntoSilla(double** matriz, int filas, int columnas, int fila, int columna) {
    for (int i = 0; i < columnas; ++i) {
        if (matriz[fila][i] < matriz[fila][columna]) return false;
    }

    for (int i = 0; i < filas; ++i) {
        if (matriz[i][columna] > matriz[fila][columna]) return false;
    }

    return true;
}

void buscarPuntoSilla(double** matriz, int filas, int columnas) {
    if (!matriz || filas == 0 || columnas == 0) {
        cout << "La matriz esta vacía o no tiene dimensiones válidas." << endl;
        return;
    }

    for (int fila = 0; fila < filas; ++fila) {
        for (int columna = 0; columna < columnas; ++columna) {
            if (verificarPuntoSilla(matriz, filas, columnas, fila, columna)) {
                cout << "Punto de silla encontrado en (" << fila + 1 << ", " << columna + 1
                     << ") con valor: " << matriz[fila][columna] << endl;
                return;
            }
        }
    }

    cout << "No se encontro ningun punto de silla en la matriz." << endl;
}

double** crearMatriz(int filas, int columnas) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new double[columnas];
        for (int j = 0; j < columnas; ++j) {
            cout << "Ingrese el valor en [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matriz[i][j];
        }
    }
    return matriz;
}

void liberarMatriz(double** matriz, int filas) {
    for (int i = 0; i < filas; ++i) delete[] matriz[i];
    delete[] matriz;
}

int main() {
    int filas, columnas;

    cout << "Ingrese el numero de filas de la matriz: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas de la matriz: ";
    cin >> columnas;

    double** matriz = crearMatriz(filas, columnas);

    buscarPuntoSilla(matriz, filas, columnas);

    liberarMatriz(matriz, filas);

    return 0;
}
