#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>


using namespace std;


mutex mtx;
int total_count = 0;


void countOccurrences(const vector<string>& arr, const string& target, int start, int end) {
    int count = 0;
    for (int i = start; i < end; ++i) {
        if (arr[i] == target) {
            count++;
        }
    }
    lock_guard<mutex> lock(mtx);
    total_count += count;
}


int main() {
    const int numThreads = 4;  // Número de hilos a utilizar
    vector<string> arr = {"hola", "mundo", "estoy", "diciendo", "hola", "hacia", "todos", "hola"};  // El arreglo de cadenas
    string target = "hola";  // La cadena que queremos contar


    int length = arr.size();
    int partSize = length / numThreads;
    vector<thread> threads;


    // Crear hilos y asignarles partes del arreglo
    for (int i = 0; i < numThreads; ++i) {
        int start = i * partSize;
        int end = (i == numThreads - 1) ? length : (i + 1) * partSize;
        threads.emplace_back(countOccurrences, ref(arr), ref(target), start, end);
    }


    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }


    // Imprimir el resultado
    cout << "La cadena \"" << target << "\" se repite " << total_count << " veces." << endl;


    return 0;
}
