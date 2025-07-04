// Transportador.cpp
#include "Transportador.h"
#include "TransportadorExceptions.h"
#include "CodigoActivo.h"
#include "ActivosExceptions.h"
#include "Boveda.h"
#include "Plaza.h"
#include <iostream>

Transportador::Transportador(const std::string& n, const std::string& c)
  : nombre(n), codigo(c) {}

void Transportador::asignarRuta(const std::vector<ParadaRuta>& ruta) {
    if (!ruta_actual.empty()) {
        throw RutaActivaException();
    }
    if (ruta.empty()) {
        throw RutaInvalidaException();
    }
    std::cout << "[Transportador " << nombre << "] Ruta asignada con " << ruta.size() << " paradas.\n";
    ruta_actual = ruta;
}

void Transportador::ejecutarRuta() {
    std::cout << "\n--- [Transportador " << nombre << "] INICIANDO RUTA ---" << std::endl;
    if (ruta_actual.empty()) {
        std::cout << "[Transportador " << nombre << "] No hay ruta programada.\n";
        return;
    }

    for (const auto& parada : ruta_actual) {
        std::cout << "\n-> Dirigiéndose a la bóveda: " << parada.boveda->getCodigo()
                  << " en " << parada.boveda->getPlaza()->ciudad << std::endl;

        try {
            switch (parada.tipo_op) {
                case TipoOperacion::RETIRO:
                    std::cout << "   Acción: Recoger activos." << std::endl;
                    parada.boveda->retirar(parada.solicitud, this);
                    carga.depositar(parada.solicitud);
                    std::cout << "   Éxito: Activos recogidos. Carga actual: " << carga.total() << std::endl;
                    break;

                case TipoOperacion::DEPOSITO:
                    std::cout << "   Acción: Entregar activos." << std::endl;
                    carga.retirar(parada.solicitud.activos);
                    parada.boveda->depositar(parada.solicitud, this);
                    std::cout << "   Éxito: Activos entregados. Carga actual: " << carga.total() << std::endl;
                    break;
                
                default:
                    throw OperacionException("Tipo de operación inválida en la ruta del transportador.");
            }
        } catch (const std::exception& e) {  // Changed to catch std::exception
            ruta_actual.clear();
            throw OperacionException("Fallo en la ruta en la bóveda " + parada.boveda->getCodigo() + ": " + e.what());
        }
    }

    std::cout << "\n--- [Transportador " << nombre << "] RUTA COMPLETADA ---\n";
    if (carga.total() > 0.01) {
         std::cerr << "ADVERTENCIA: El transportador finalizó la ruta con carga residual: " << carga.total() << std::endl;
    }
    ruta_actual.clear();
}