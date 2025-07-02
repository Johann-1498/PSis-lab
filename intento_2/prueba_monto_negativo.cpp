#include "Activos.h"
#include "SolicitudActivos.h"
#include <iostream>

int main() {
    Activos activos;
    SolicitudActivos solicitud;
    solicitud.activos = {{CodigoActivo::DOLARES, -100.0}};
    
    try {
        std::cout << "Intentando depositar monto negativo..." << std::endl;
        activos.depositar(solicitud);
        
        std::cerr << "ERROR: No se lanzó la excepción" << std::endl;
        return 1;
    } 
    catch (const MontoNegativoException& e) {
        std::cout << "SUCCESS: Excepción capturada:\n" << e.what() << std::endl;
        return 0;
    }
    catch (...) {
        std::cerr << "ERROR: Excepción inesperada" << std::endl;
        return 1;
    }
}
