#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>

struct Cancion {
    int id;
    int cantidadEscuchas = 0;
    double sumaCalificaciones = 0.0;

    double promedio() const {
        return cantidadEscuchas == 0 ? 0.0 : sumaCalificaciones / cantidadEscuchas;
    }

    bool operator<(const Cancion& otra) const {
        return this->promedio() < otra.promedio();
    }
};

class RankingCanciones {
private:
    std::vector<Cancion> heap;

    void maxHeapify(int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l] < heap[largest]) largest = l;
        if (r < heap.size() && heap[r] < heap[largest]) largest = r;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

    void buildHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            maxHeapify(i);
        }
    }

    void maxHeapifyRec(std::vector<Cancion>& h, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < h.size() && h[largest] < h[l]) largest = l;
        if (r < h.size() && h[largest] < h[r]) largest = r;

        if (largest != i) {
            std::swap(h[i], h[largest]);
            maxHeapifyRec(h, largest);
        }
    }

public:
    void insertarCanciones(const std::unordered_map<int, Cancion>& cancionesMap) {
        for (const auto& [id, c] : cancionesMap)
            heap.push_back(c);
        buildHeap();
    }

    void mostrarTop(int n) {
        std::vector<Cancion> copia = heap;
        for (int i = 0; i < n && !copia.empty(); ++i) {
            std::cout << "Cancion ID: " << copia[0].id << " | Promedio: " << copia[0].promedio() << "\n";
            std::swap(copia[0], copia.back());
            copia.pop_back();
            maxHeapifyRec(copia, 0);
        }
    }
};