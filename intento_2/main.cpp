#include "SistemaBancario.h"
#include <iostream>

int main() {
    try {
        SistemaBancario sistema;
        sistema.run();
    } catch (const std::exception& e) {
        std::cerr << "Error fatal no controlado en main: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}