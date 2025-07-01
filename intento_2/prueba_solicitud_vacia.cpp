// prueba_solicitud_vacia.cpp
#include <iostream>
#include "Registro.h"
#include "SolicitudActivosExceptions.h"
#include "Boveda.h"
#include "Banco.h" // Necesario para Banco

int main() {
    Banco banco("MI_BANCO"); // Banco necesita nombre
    Boveda boveda("BOVEDA_TEST");
    SolicitudActivos solicitudVacia;
    
    try {
        std::cout << "Intentando crear registro con solicitud vacía..." << std::endl;
        Registro registro(TipoOperacion::DEPOSITO, solicitudVacia, &boveda);
    } catch (const SolicitudVaciaException& e) {
        std::cerr << "✅ Excepción capturada correctamente:\n" << e.what() << std::endl;
    }
    return 0;
}