#include <iostream>
#include "OutputException.h"

void escribirSalida(bool dispositivoConectado) {
    if (!dispositivoConectado) {
        throw OutputException("No se detecto un dispositivo de salida.");
    }
}

int main() {
    //Simulando el fallo para lanzar la excepcion OutputException
    try {
        escribirSalida(false);
    } catch (const ComputerException& e) {
        std::cerr << "Error capturado: " << e.what() << std::endl;
    }

    return 0;
}
