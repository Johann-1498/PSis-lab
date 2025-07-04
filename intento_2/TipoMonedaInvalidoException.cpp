#include "Activos.h"
#include "ActivosExceptions.h"
using namespace std;

int main() {
    try {
        // Intentar crear moneda con código inválido
        Moneda monedaInvalida(CodigoActivo::BONO); // BONO no es tipo moneda
    } catch (const TipoMonedaInvalidoException& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
        // Salida esperada: "[OperacionException] [Activos] Código inválido para moneda: 20"
    }
    return 0;
}