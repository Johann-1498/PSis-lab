#include <iostream>
using namespace std;

int** crearMatriz(int filas, int columnas) {
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas];
    }
    return matriz;
}

// liberar memoria de una matriz
void liberarMatriz(int** matriz, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void llenarMatriz(int** matriz, int filas, int columnas) {
    cout << "Ingrese los elementos de la matriz:" << endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> *(*(matriz + i) + j);
        }
    }
}

// Función para multiplicar matrices usando punteros
int** multiplicarMatrices(int** a, int** b, int filas_a, int columnas_a, int columnas_b) {
    int** resultado = crearMatriz(filas_a, columnas_b);
    
    for (int i = 0; i < filas_a; ++i) {
        for (int j = 0; j < columnas_b; ++j) {
            *(*(resultado + i) + j) = 0; // Inicializar a 0
            
            for (int k = 0; k < columnas_a; ++k) {
                *(*(resultado + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
            }
        }
    }
    
    return resultado;
}

// Función para imprimir una matriz
void imprimirMatriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << *(*(matriz + i) + j) << "\t";
        }
        cout << endl;
    }
}

int main() {
    int filas_a, columnas_a, filas_b, columnas_b;
    
    cout << "Ingrese las dimensiones de la matriz A (filas - columnas): ";
    cin >> filas_a >> columnas_a;
    
    cout << "Ingrese las dimensiones de la matriz B (filas - columnas): ";
    cin >> filas_b >> columnas_b;
    
    // Verificar si las matrices se pueden multiplicar
    if (columnas_a != filas_b) {
        cerr << "Error: Las dimensiones de las matrices no son compatibles para multiplicaciOn." << endl;
        cerr << "El numero de columnas de A debe ser igual al numero de filas de B." << endl;
        return 1;
    }
    
    // Crear y llenar las matrices
    int** matrizA = crearMatriz(filas_a, columnas_a);
    int** matrizB = crearMatriz(filas_b, columnas_b);
    
    cout << "\nMatriz A:" << endl;
    llenarMatriz(matrizA, filas_a, columnas_a);
    
    cout << "\nMatriz B:" << endl;
    llenarMatriz(matrizB, filas_b, columnas_b);
    
    // Multiplicar matrices
    int** resultado = multiplicarMatrices(matrizA, matrizB, filas_a, columnas_a, columnas_b);
    
    // Imprimir resultados
    cout << "\nMatriz A:" << endl;
    imprimirMatriz(matrizA, filas_a, columnas_a);
    
    cout << "\nMatriz B:" << endl;
    imprimirMatriz(matrizB, filas_b, columnas_b);
    
    cout << "\nResultado de A x B:" << endl;
    imprimirMatriz(resultado, filas_a, columnas_b);
    
    // Liberar memoria
    liberarMatriz(matrizA, filas_a);
    liberarMatriz(matrizB, filas_b);
    liberarMatriz(resultado, filas_a);
    
    return 0;
}