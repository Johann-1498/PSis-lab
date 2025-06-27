#include <iostream>
#include "ComputerException.h"
#include "InputException.h"
#include "ProcessorException.h"
#include "OutputException.h"

void leerArchivo(const std::string& ruta) {
    std::cout << "Leyendo archivo en: " << ruta << std::endl;
}

void procesarDatos(int valor) {
    std::cout << "Procesando valor: " << valor << std::endl;
}

void escribirSalida(bool dispositivoConectado) {
    std::cout << "Escribiendo en dispositivo conectado.\n";
}

int main() {
    try {
        leerArchivo("ejemplo.txt");
        procesarDatos(1);
        escribirSalida(true);
        std::cout << "Proceso completo sin errores.\n";
    } catch (const ComputerException& e) {
        std::cerr << "Error capturado: " << e.what() << std::endl;
    }

    return 0;
}
