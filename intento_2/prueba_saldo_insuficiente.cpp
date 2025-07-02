#include <iostream>
#include "Boveda.h"
#include "Plaza.h"
#include "SolicitudActivos.h"
#include "BancoExceptions.h"
#include "Transportador.h"

int main() {
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
        
        std::cerr << "ERROR: Incidencia capturada!" << std::endl;
        return 1;
    } 
    catch (const SaldoInsuficienteException& e) {
        std::cout << "SUCCESS: Excepcion capturada correcamente:\n" 
                  << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR INESPERADO: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}