// prueba_boveda_no_encontrada.cpp
#include <iostream>
#include "Banco.h"
#include "BancoExceptions.h"
#include "Plaza.h"

int main() {
    try {
        // Initialize objects
        Plaza plazaCentral("Plaza Central");
        plazaCentral.codigo = "PLZ001";
        plazaCentral.direccion = "Av. Principal 123";

        Banco banco("Mi Banco");
        
        // Setup test environment
        banco.agregarBoveda("BOVEDA_1", &plazaCentral);
        banco.agregarBoveda("BOVEDA_2", &plazaCentral);

        // Test case
        std::cout << "Intentando acceder a una boveda inexistente..." << std::endl;
        auto boveda = banco.getBoveda("BOVEDA_INEXISTENTE");
        
        std::cerr << "ERROR: No se pudo acceder!" << std::endl;
        return 1;  // Test failed
    } 
    catch (const BovedaNoEncontradaException& e) {
        std::cout << "EXITO: Excepcion detectada correctamente :\n" 
                  << e.what() << std::endl;
        return 0;  // Test passed
    }
    catch (...) {
        std::cerr << "ERROR: Excepcion erronea!" << std::endl;
        return 1;  // Test failed
    }
}