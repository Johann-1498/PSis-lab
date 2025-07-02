#include <iostream>
#include <unordered_map>
#include "Boveda.h"
#include "Plaza.h"
#include "SolicitudActivos.h"
#include "BancoExceptions.h"
#include "Transportador.h"
#include "Activos.h"
#include "ActivosExceptions.h"

void testSaldoInsuficiente() {
    try {
        // 1. Setup test environment
        Plaza plazaCentral("Lima");
        Boveda boveda("B001", &plazaCentral);
        Transportador transporter("Transport-01", "T001");

        // 2. Create withdrawal request (USD 1000)
        SolicitudActivos withdrawalRequest;
        withdrawalRequest.activos[CodigoActivo::DOLARES] = 1000.0;

        // 3. Show initial state
        std::cout << "=== Saldo Insuficiente TEST ===" << std::endl;
        std::cout << "Valor inicial: $" 
                  << boveda.totalPorActivo(CodigoActivo::DOLARES) << std::endl;

        // 4. Attempt withdrawal (should fail)
        std::cout << "Intentando retirar $1000 sin fondos..." << std::endl;
        boveda.retirar(withdrawalRequest, &transporter);
        
        std::cerr << "ERROR: Incidencia no capturada!" << std::endl;
    } 
    catch (const SaldoInsuficienteException& e) {
        std::cout << "SUCCESS: Excepcion capturada correctamente:\n" 
                  << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR INESPERADO: " << e.what() << std::endl;
    }
}

void testActivoNoExistente() {
    std::cout << "\n=== Activo No Existente TEST ===" << std::endl;
    
    Activos activos;
    // Crear una SolicitudActivos con un código inválido
    SolicitudActivos solicitud;
    solicitud.activos[static_cast<CodigoActivo>(99)] = 100; // Código inválido
    
    try {
        // Intentar operar con un activo que no existe
        std::cout << "Intentando depositar en activo inexistente (99)..." << std::endl;
        activos.depositar(solicitud);
        
        std::cerr << "ERROR: Excepcion no capturada!" << std::endl;
    } 
    catch (const ActivoNoExisteException& e) {
        std::cout << "SUCCESS: Excepcion capturada correctamente:\n"
                  << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR INESPERADO: " << e.what() << std::endl;
    }
}

int main() {
    // Ejecutar ambas pruebas
    testSaldoInsuficiente();
    testActivoNoExistente();
    
    return 0;
}