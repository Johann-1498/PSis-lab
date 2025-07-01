#include <iostream>
#include <vector>
#include "Plaza.h"
#include "Banco.h"
#include "Transportador.h"
#include "OperacionException.h"

#include "CodigoActivo.h"  // Si necesitan usar el enum directamente
#include "ActivosExceptions.h"  // Si necesitan lanzar excepciones


void imprimirEstadoBoveda(const Boveda& boveda) {
    std::cout << "--- Estado Bóveda: " << boveda.getCodigo() << " ---\n";
    std::cout << "  Soles:   " << boveda.totalPorActivo(CodigoActivo::SOLES) << "\n";
    std::cout << "  Dólares: " << boveda.totalPorActivo(CodigoActivo::DOLARES) << "\n";
    std::cout << "  Bonos:   " << boveda.totalPorActivo(CodigoActivo::BONO) << "\n";
    std::cout << "  Total:   " << boveda.total() << "\n";
    std::cout << "-------------------------------------\n";
}

int main() {
    try {
        // 1. Configuración del entorno
        std::cout << "--- CONFIGURANDO ENTORNO ---\n";
        Plaza plaza_lima{"Lima", "Av. Principal 123", "LIM01"};
        Plaza plaza_aqp{"Arequipa", "Calle Mercaderes 456", "AQP01"};

        Banco banco_bcp("BCP");
        Banco banco_bbva("BBVA");

        banco_bcp.agregarBoveda("BCP_LIM_CENTRAL", &plaza_lima);
        banco_bbva.agregarBoveda("BBVA_AQP_SUR", &plaza_aqp);

        Transportador hermes("Hermes", "HER001");

        // 2. Cargar fondos iniciales en la bóveda de origen
        std::cout << "\n--- DEPOSITO INICIAL ---\n";
        Boveda* boveda_origen = banco_bcp.getBoveda("BCP_LIM_CENTRAL");
        if (!boveda_origen) return 1;

        SolicitudActivos deposito_inicial = {
            {CodigoActivo::SOLES, 50000.0},
            {CodigoActivo::DOLARES, 20000.0},
            {CodigoActivo::BONO, 100.0}
        };
        boveda_origen->depositar(deposito_inicial);
        imprimirEstadoBoveda(*boveda_origen);
        
        Boveda* boveda_destino = banco_bbva.getBoveda("BBVA_AQP_SUR");
        if (!boveda_destino) return 1;
        imprimirEstadoBoveda(*boveda_destino);


        // 3. El banco BCP inicia una solicitud de traslado
        // Quiere mover activos de su bóveda en Lima a una bóveda de BBVA en Arequipa
        std::cout << "\n--- INICIANDO SOLICITUD DE TRASLADO ---\n";
        SolicitudActivos solicitud_traslado = {
            {CodigoActivo::SOLES, 15000.0},
            {CodigoActivo::BONO, 25.0}
        };
        
        // El banco BCP orquesta la operación
        banco_bcp.iniciarTrasladoInterbancario(
            boveda_origen,
            boveda_destino,
            &hermes,
            solicitud_traslado
        );

        // 4. Verificar el estado final
        std::cout << "\n--- ESTADO FINAL DE LAS BÓVEDAS ---\n";
        imprimirEstadoBoveda(*boveda_origen);
        imprimirEstadoBoveda(*boveda_destino);
        
        std::cout << "\n--- ESTADO FINAL TRANSPORTADOR ---\n";
        std::cout << "Carga final de " << hermes.getNombre() << ": " << hermes.totalEnCarga() << std::endl;
        
    } catch (const OperacionException& e) {
        std::cerr << "\n!!!! ERROR DE OPERACION: " << e.what() << "!!!!" << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n!!!! ERROR INESPERADO: " << e.what() << "!!!!" << std::endl;
        return 1;
    }

    return 0;
}