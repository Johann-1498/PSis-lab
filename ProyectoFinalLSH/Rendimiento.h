#pragma once
#include <chrono>
#include <iostream>

class Rendimiento {
private:
    std::chrono::high_resolution_clock::time_point inicio;

public:
    void iniciar() {
        inicio = std::chrono::high_resolution_clock::now();
    }

    void finalizar(const std::string& mensaje = "⏱ Tiempo transcurrido") {
        auto fin = std::chrono::high_resolution_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
        std::cout << mensaje << ": " << duracion.count() << " ms\n";
    }
};
