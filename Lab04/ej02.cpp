#include <iostream>
#include <vector>

using namespace std;

bool verificarPuntosSilla(const vector<vector<double>>& matrix, int fila, int
columna) {
    // verificar si el elemento actual es el menor de la fila
    for (int i = 0; i < matrix.size(); i++) {
    if (matrix[fila][i] < matrix[fila][columna]) {
        return false;
    }
}

// verificar si el elemento actual es el mayor en la columna
    for (int i = 0; i < matrix[0].size(); i++) {
        if (matrix[i][columna] > matrix[fila][columna]) {
            return false;
        }
    }

    return true;
}

void buscarPuntoSilla(const vector<vector<double>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        cout << "La matriz está vacía o no tiene columna." << endl;
        return;
    }

    for (int fila = 0; fila < matrix.size(); fila++) {
        for (int columna = 0; columna < matrix[0].size(); columna++) {
            if (verificarPuntosSilla(matrix, fila, columna)) {
                cout << "Punto de silla encontrado en la posicion (" << fila + 1
                << ", " << columna + 1 << ") con valor: " << matrix[fila][columna] << endl;
                return;
            }
        }
    }

    cout << "No se encontro ningun punto de silla en la matriz." << endl;
}

int main() {
// matrices ejemploo
vector<vector<double>> matrix = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
vector<vector<double>> matrix2 = {
    {3, 1, 2},
    {6, 5, 4},
    {9, 7, 8}
};
vector<vector<double>> matrix3 = {
    {13, 1, 2},
    {6, 15, 4},
    {9, 7, 18}
};
buscarPuntoSilla(matrix);
buscarPuntoSilla(matrix2);
buscarPuntoSilla(matrix3);

return 0;
}
