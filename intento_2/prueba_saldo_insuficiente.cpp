// prueba_saldo_insuficiente.cpp
#include <iostream>
#include "Boveda.h"
#include "BancoExceptions.h"
#include "SolicitudActivos.h"
#include "CodigoActivo.h"

int main() {
    Banco banco("MI_BANCO"); // Banco necesita nombre
    Boveda boveda("BOVEDA_TEST");
    SolicitudActivos solicitud = {{CodigoActivo::DOLARES, 1000}};
    
    try {
        std::cout << "Intentando retirar $1000 de bóveda vacía..." << std::endl;
        boveda.retirar(solicitud, nullptr);
    } catch (const SaldoInsuficienteException& e) {
        std::cerr << "✅ Excepción capturada correctamente:\n" << e.what() << std::endl;
    }
    return 0;
}