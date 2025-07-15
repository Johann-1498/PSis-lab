// --- Archivo: RankingCanciones.h (CORREGIDO) ---
#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm> // Para std::make_heap y std::sort_heap
#include <functional>
#include "Cancion.h"

class RankingCanciones {
private:
    std::vector<Cancion> heap;

public:
    void insertarCanciones(const std::unordered_map<int, Cancion>& cancionesMap) {
        heap.reserve(cancionesMap.size());
        for (const auto& par : cancionesMap) {
            heap.push_back(par.second);
        }

        // --- SOLUCIÓN AL CRASH ---
        // Se reemplaza la construcción manual y con hilos (que causaba el error)
        // por la función estándar de C++. Es segura, correcta y muy optimizada.
        std::make_heap(heap.begin(), heap.end());
    }

    void mostrarTop(int n) {
        std::vector<Cancion> copia = heap;
        
        // Convierte la copia del heap en un vector ordenado de menor a mayor.
        // Es más eficiente que extraer elementos uno por uno.
        std::sort_heap(copia.begin(), copia.end());

        int count = 0;
        // Se itera desde el final del vector (los elementos más grandes) hacia atrás.
        for (auto it = copia.rbegin(); it != copia.rend() && count < n; ++it, ++count) {
             std::cout << "Cancion ID: " << it->id
                      << " - Promedio: " << it->promedio() << "\n";
        }
    }
};