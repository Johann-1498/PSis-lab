// prueba_boveda_no_encontrada.cpp
#include <iostream>
#include "Banco.h"
#include "BancoExceptions.h"
#include "Plaza.h" // Necesario para crear Banco

int main() {
    Plaza plazaCentral("Plaza Central");
    Banco banco("Mi Banco", &plazaCentral); // Requiere Plaza
    
    try {
        std::cout << "Intentando acceder a bóveda inexistente..." << std::endl;
        auto boveda = banco.getBoveda("BOVEDA_INEXISTENTE");
    } catch (const BovedaNoEncontradaException& e) {
        std::cerr << " Excepción capturada correctamente:\n" << e.what() << std::endl;
    }
    return 0;
}