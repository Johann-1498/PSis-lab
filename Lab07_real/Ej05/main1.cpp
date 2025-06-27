#include <iostream>
#include "InputException.h"

void leerArchivo(const std::string& ruta) {
    if (ruta.empty()) {
        throw InputException("Ruta vacia al intentar abrir archivo.");
    }
    // Simular fallo paara ejecutar la excepcion InputException
    throw InputException("Archivo no encontrado: " + ruta);
}

int main() {
    try {
        leerArchivo("");
    } catch (const ComputerException& e) {
        std::cerr << "Error capturado: " << e.what() << std::endl;
    }

    return 0;
}
