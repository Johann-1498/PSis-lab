#include "Activos.h"
#include "SolicitudActivosExceptions.h"

int main() {
    Activos activos;
    SolicitudActivos solicitud = {{CodigoActivo::DOLARES, -100}}; // Monto negativo
    
    try {
        // Intentar depositar monto negativo
        activos.depositar(solicitud);
    } catch (const MontoNegativoException& e) {
        std::cerr << "Excepción capturada: " << e.what() << std::endl;
        // Salida esperada mostrará el activo y monto negativo
    }
    return 0;
}