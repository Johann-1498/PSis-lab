#include <iostream>
#include "ProcessorException.h"

void procesarDatos(int valor) {
    if (valor < 0) {
        throw ProcessorException("No se puede procesar un valor negativo.");
    }
}

int main() {
    //Siumula el fallo para lanzar la excepcion  ProcessorException
    try {
        procesarDatos(-5);
    } catch (const ComputerException& e) {
        std::cerr << "Error capturado: " << e.what() << std::endl;
    }

    return 0;
}
