#include <iostream>
#include <thread>
#include <vector>
#include <algorithm> // Para std::max_element
#include <limits>    // Para std::numeric_limits


using namespace std;


void findMaxPart(const vector<int>& arr, int start, int end, int& maxVal) {
    maxVal = *max_element(arr.begin() + start, arr.begin() + end);
}


int main() {
    const int numThreads = 4;  // Número de hilos a utilizar
    vector<int> arr(1000000);  // Un arreglo muy grande


    // Inicializar el arreglo con valores aleatorios
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = rand();
    }


    int length = arr.size();
    int partSize = length / numThreads;
    vector<thread> threads;
    vector<int> maxVals(numThreads, numeric_limits<int>::min());


    // Crear hilos y asignarles partes del arreglo
    for (int i = 0; i < numThreads; ++i) {
        int start = i * partSize;
        int end = (i == numThreads - 1) ? length : (i + 1) * partSize;
        threads.emplace_back(findMaxPart, ref(arr), start, end, ref(maxVals[i]));
    }


    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }


    // Encontrar el valor máximo entre los resultados parciales
    int maxVal = *max_element(maxVals.begin(), maxVals.end());


    // Imprimir el resultado
    cout << "El valor máximo del arreglo es: " << maxVal << endl;


    return 0;
}
