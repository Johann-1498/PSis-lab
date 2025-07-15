#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>


using namespace std;


mutex mtx;
bool found = false;
int foundIndex = -1;


void binarySearch(const vector<int>& arr, int target, int start, int end) {
    while (start <= end) {
        if (found) return;  // Si ya se encontró el elemento en otro hilo, salimos


        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            lock_guard<mutex> lock(mtx);
            if (!found) {
                found = true;
                foundIndex = mid;
            }
            return;
        }
        else if (arr[mid] < target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
}


int main() {
    const int numThreads = 4;
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31};
    int target = 19;


    int length = arr.size();
    int partSize = length / numThreads;
    vector<thread> threads;


    // Lanzar hilos para realizar la búsqueda binaria en partes del arreglo
    for (int i = 0; i < numThreads; ++i) {
        int start = i * partSize;
        int end = (i == numThreads - 1) ? length - 1 : (start + partSize - 1);
        threads.emplace_back(binarySearch, ref(arr), target, start, end);
    }


    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }


    // Imprimir el resultado
    if (found) {
        cout << "Elemento encontrado en el índice: " << foundIndex << endl;
    } else {
        cout << "Elemento no encontrado." << endl;
    }


    return 0;
}
