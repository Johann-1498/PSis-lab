#include <iostream>
using namespace std;

bool verificarPuntoSilla(double** matriz, int filas, int columnas, int fila, int columna) {
    // Verificar si es el mínimo de su fila
    for (int i = 0; i < columnas; ++i) {
        if (matriz[fila][i] < matriz[fila][columna]) {
            return false;
        }
    }

    // Verificar si es el máximo de su columna
    for (int i = 0; i < filas; ++i) {
        if (matriz[i][columna] > matriz[fila][columna]) {
            return false;
        }
    }

    return true;
}

void buscarPuntoSilla(double** matriz, int filas, int columnas) {
    if (matriz == nullptr || filas == 0 || columnas == 0) {
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

double** crearMatriz(int filas, int columnas, const double datos[][3]) {
    double** matriz = new double*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new double[columnas];
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = datos[i][j];
        }
    }
    return matriz;
}

void liberarMatriz(double** matriz, int filas) {
    for (int i = 0; i < filas; ++i)
        delete[] matriz[i];
    delete[] matriz;
}

int main() {
    const int filas = 3, columnas = 3;

    double datos1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    double datos2[3][3] = {
        {3, 1, 2},
        {6, 5, 4},
        {9, 7, 8}
    };

    double datos3[3][3] = {
        {13, 1, 2},
        {6, 15, 4},
        {9, 7, 18}
    };

    double** m1 = crearMatriz(filas, columnas, datos1);
    double** m2 = crearMatriz(filas, columnas, datos2);
    double** m3 = crearMatriz(filas, columnas, datos3);

    buscarPuntoSilla(m1, filas, columnas);
    buscarPuntoSilla(m2, filas, columnas);
    buscarPuntoSilla(m3, filas, columnas);

    liberarMatriz(m1, filas);
    liberarMatriz(m2, filas);
    liberarMatriz(m3, filas);

    return 0;
}
