#include <iostream>
#include <thread>
#include <vector>
#include <numeric>  // for std::accumulate


using namespace std;


void sumArrayPart(const vector<int>& arr, int start, int end, long long& result) {
    result = accumulate(arr.begin() + start, arr.begin() + end, 0LL);
}


int main() {
    const int numThreads = 4;  // Número de hilos a utilizar
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // El arreglo a sumar


    int length = arr.size();
    int partSize = length / numThreads;
    vector<thread> threads;
    vector<long long> results(numThreads, 0);


    // Crear hilos y asignarles partes del arreglo
    for (int i = 0; i < numThreads; ++i) {
        int start = i * partSize;
        int end = (i == numThreads - 1) ? length : (i + 1) * partSize;
        threads.emplace_back(sumArrayPart, ref(arr), start, end, ref(results[i]));
    }


    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }


    // Sumar los resultados parciales
    long long totalSum = accumulate(results.begin(), results.end(), 0LL);


    // Imprimir el resultado
    cout << "La suma total de los elementos del arreglo es: " << totalSum << endl;


    return 0;
}
