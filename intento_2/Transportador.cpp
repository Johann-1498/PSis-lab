#include "Transportador.h"
#include "TransportadorExceptions.h"

#include "Boveda.h"
#include "Plaza.h"
#include <iostream>

Transportador::Transportador(const std::string& n, const std::string& c)
  : nombre(n), codigo(c) {}

void Transportador::asignarRuta(const std::vector<ParadaRuta>& ruta) {
    if (!ruta_actual.empty()) {
          throw RutaActivaException(); //El transportador ya tiene una ruta activa
    }
     if (ruta.empty()) {
        throw RutaInvalidaException(); // Cambiado
    }
    // Validar si la ruta es factible (aquí iría la lógica de negocio)
    // Por ahora, aceptamos cualquier ruta.
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
                    // Bóveda entrega activos al transportador
                    parada.boveda->retirar(parada.solicitud, this);
                    // Transportador recibe los activos en su carga
                    carga.depositar(parada.solicitud);
                    std::cout << "   Éxito: Activos recogidos. Carga actual: " << carga.total() << std::endl;
                    break;

                case TipoOperacion::DEPOSITO:
                    std::cout << "   Acción: Entregar activos." << std::endl;
                    // Transportador retira de su carga
                    carga.retirar(parada.solicitud);
                    // Bóveda recibe los activos
                    parada.boveda->depositar(parada.solicitud, this);
                    std::cout << "   Éxito: Activos entregados. Carga actual: " << carga.total() << std::endl;
                    break;
                
                default:
                    throw OperacionException("Tipo de operación inválida en la ruta del transportador.");
            }
        } catch (const std::runtime_error& e) {
            // Limpiar ruta y lanzar una excepción más específica
            ruta_actual.clear();
            throw OperacionException("Fallo en la ruta en la bóveda " + parada.boveda->getCodigo() + ": " + e.what());
        }
    }

    std::cout << "\n--- [Transportador " << nombre << "] RUTA COMPLETADA ---\n";
    if (carga.total() > 0.01) { // Usar una tolerancia para el double
         std::cerr << "ADVERTENCIA: El transportador finalizó la ruta con carga residual: " << carga.total() << std::endl;
    }
    ruta_actual.clear();
}