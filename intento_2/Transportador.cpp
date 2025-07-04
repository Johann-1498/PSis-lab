#include "Transportador.h"
#include "Banco.h"
#include "Boveda.h"
#include "DataTypes.h"
#include "Registro.h"
#include "excepciones/TransportadorExceptions.h"
#include "excepciones/OperacionException.h"
#include <iostream>

RutaActivaException::RutaActivaException() : TransportadorException("El transportador ya tiene carga y no puede iniciar una nueva ruta.") {}
FalloEnRutaException::FalloEnRutaException(const std::string& boveda_fallo, const std::string& motivo)
    : TransportadorException("Fallo en la ruta en la bóveda '" + boveda_fallo + "'. Motivo: " + motivo) {}

Transportador::Transportador(const std::string& nombre) : nombre(nombre) {}
void Transportador::limpiarCarga() { carga = Activos(); }

std::vector<Registro> Transportador::ejecutarRuta(const std::vector<ParadaRuta>& ruta, Banco* banco_contexto) {
    if (carga.totalGeneral() > 0.01) throw RutaActivaException();
    
    std::cout << "\n--- [Transportador " << nombre << "] INICIANDO RUTA ---\n";
    std::vector<Registro> registros_ruta;

    for (const auto& parada : ruta) {
        std::cout << "  -> Parada en Bóveda: " << parada.codigo_boveda << std::endl;
        try {
            Boveda* boveda_actual = banco_contexto->getBoveda(parada.codigo_boveda);
            
            if (parada.tipo == TipoParada::RECOGER) {
                boveda_actual->retirar(parada.codigo_activo, parada.monto);
                carga.depositar(parada.codigo_activo, parada.monto);
                std::cout << "     Acción: RECOGER. Éxito.\n";
            } else {
                carga.retirar(parada.codigo_activo, parada.monto);
                boveda_actual->depositar(parada.codigo_activo, parada.monto);
                std::cout << "     Acción: ENTREGAR. Éxito.\n";
            }
            registros_ruta.emplace_back(parada, boveda_actual, this);

        } catch (const OperacionException& e) {
            limpiarCarga();
            throw FalloEnRutaException(parada.codigo_boveda, e.what());
        }
    }
    std::cout << "--- RUTA COMPLETADA ---\n";
    if (carga.totalGeneral() > 0.01) {
        std::cerr << "ADVERTENCIA: El transportador finalizó con carga residual de " << carga.totalGeneral() << "!\n";
    }
    limpiarCarga();
    return registros_ruta;
}

void Transportador::imprimirEstado() const {
    std::cout << "\n--- Estado del Transportador: " << nombre << " ---\n";
    std::cout << "  Carga actual:\n";
    carga.imprimirEstado();
}