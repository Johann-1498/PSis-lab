#include "Activos.h"
#include "ActivosExceptions.h"

int main() {
    Activos activos;
    SolicitudActivos solicitud = {{static_cast<CodigoActivo>(99), 100}}; // Código inválido
    
    try {
        // Intentar operar con un activo que no existe
        activos.depositar(solicitud);
    } catch (const ActivoNoExisteException& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
        // Salida esperada: "[OperacionException] [Activos] Activo no existe: 99"
    }
    return 0;
}