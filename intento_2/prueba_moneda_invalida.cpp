// prueba_moneda_invalida.cpp
#include <iostream>
#include "Activos.h"
#include "ActivosExceptions.h"
#include "CodigoActivo.h"

int main() {
    try {
        std::cout << "Intentando crear moneda con codigo de bono..." << std::endl;
        Moneda monedaInvalida(CodigoActivo::BONO); // BONO no es tipo moneda
    } catch (const TipoMonedaInvalidoException& e) {
        std::cerr << "Excepcion capturada correctamente:\n" << e.what() << std::endl;
    }
    return 0;
}