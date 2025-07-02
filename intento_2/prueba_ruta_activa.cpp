// test_ruta_activa.cpp
#include <iostream>
#include "Transportador.h"
#include "Boveda.h"
#include "Plaza.h"
#include "TransportadorExceptions.h"

void testRutaActiva() {
    try {
        // 1. Preparar el entorno de prueba
        Plaza plazaCentral("Lima");
        Boveda boveda1("B001", &plazaCentral);
        Boveda boveda2("B002", &plazaCentral);
        
        Transportador transporter("Trans-001", "T001");
        
        // 2. Crear rutas
        std::vector<ParadaRuta> ruta1 = {
            {&boveda1, TipoOperacion::RETIRO, SolicitudActivos{}},
            {&boveda2, TipoOperacion::DEPOSITO, SolicitudActivos{}}
        };
        
        std::vector<ParadaRuta> ruta2 = {
            {&boveda2, TipoOperacion::RETIRO, SolicitudActivos{}},
            {&boveda1, TipoOperacion::DEPOSITO, SolicitudActivos{}}
        };
        
        // 3. Asignar primera ruta (debería funcionar)
        transporter.asignarRuta(ruta1);
        std::cout << "Primera ruta asignada correctamente\n";
        
        // 4. Intentar asignar segunda ruta (debería fallar)
        transporter.asignarRuta(ruta2);
        std::cerr << "ERROR: No se lanzo la excepción esperada\n";
        
    } catch (const RutaActivaException& e) {
        std::cout << "Prueba exitosa: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "=== Probando excepcion de ruta activa ===\n";
    testRutaActiva();
    return 0;
}