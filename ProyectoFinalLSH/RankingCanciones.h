#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include "cancion.h"

class RankingCanciones {
private:
    std::vector<Cancion> heap;

    void maxHeapify(int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[largest] < heap[l]) largest = l;
        if (r < heap.size() && heap[largest] < heap[r]) largest = r;

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

    void construirHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; --i)
            maxHeapify(i);
    }

public:
    void insertarCanciones(const std::unordered_map<int, Cancion>& cancionesMap) {
        for (const auto& [id, c] : cancionesMap)
            heap.push_back(c);
        construirHeap();
    }

    void mostrarTop(int n) {
        std::vector<Cancion> copia = heap;
        for (int i = 0; i < n && !copia.empty(); ++i) {
            std::cout << "Cancion ID: " << copia[0].id
                      << "-Promedio: " << copia[0].promedio() << "\n";
            std::swap(copia[0], copia.back());
            copia.pop_back();
            heapifyTemporal(copia, 0);
        }
    }

private:
    void heapifyTemporal(std::vector<Cancion>& h, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < h.size() && h[largest] < h[l]) largest = l;
        if (r < h.size() && h[largest] < h[r]) largest = r;

        if (largest != i) {
            std::swap(h[i], h[largest]);
            heapifyTemporal(h, largest);
        }
    }
};
