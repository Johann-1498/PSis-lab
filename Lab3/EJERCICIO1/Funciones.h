#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <iostream>

template<typename T>
void mostrarVector(const std::vector<T>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << ", ";
    }
    std::cout << "]";
}

template<typename T>
void mostrarMatriz(const std::vector<std::vector<T>>& mat) {
    std::cout << "[\n";
    for (const auto& fila : mat) {
        std::cout << "  ";
        mostrarVector(fila);
        std::cout << "\n";
    }
    std::cout << "]";
}

#endif // FUNCIONES_H
