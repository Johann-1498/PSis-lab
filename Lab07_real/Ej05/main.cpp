#include <iostream>
#include "InputException.h"
#include "ProcessorException.h"
#include "OutputException.h"

void leerArchivo(const std::string& ruta) {
    if (ruta.empty()) {
        throw InputException("Ruta del archivo vacía.");
    }
    // Simular error de lectura
    throw InputException("No se pudo abrir el archivo: " + ruta);
}

int main() {
    try {
        leerArchivo("ejemplo.txt");
    } catch (const ComputerException& e) {
        std::cerr << "Error capturado: " << e.what() << std::endl;
    }

    return 0;
}
