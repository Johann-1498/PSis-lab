#include "Banco.h"
#include "Plaza.h"
#include <iostream>
#include <numeric>

Banco::Banco(const std::string& nombre) : nombre(nombre), saldo_BCR(0.0) {}

void Banco::agregarBoveda(const std::string& codigo_boveda, Plaza* p) {
    bovedas.push_back(std::make_unique<Boveda>(codigo_boveda, p));
    std::cout << "[Banco " << nombre << "] Bóveda " << codigo_boveda << " agregada en " << p->ciudad << ".\n";
}

Boveda* Banco::getBoveda(const std::string& codigo_boveda) {
    for (const auto& boveda_ptr : bovedas) {
        if (boveda_ptr->getCodigo() == codigo_boveda) {
            return boveda_ptr.get();
        }
    }
    //return nullptr;
    throw BovedaNoEncontradaException(codigo_boveda); // Cambiado

}

void Banco::iniciarTrasladoInterbancario(Boveda* origen, Boveda* destino, Transportador* transportador, const SolicitudActivos& solicitud) {
    std::cout << "\n======================================================\n";
    std::cout << "[Banco " << nombre << "] Iniciando traslado desde " << origen->getCodigo()
              << " hacia " << destino->getCodigo() << " via " << transportador->getNombre() << ".\n";
    std::cout << "======================================================\n";

    if (!origen || !destino || !transportador) {
        throw std::invalid_argument("Argumentos nulos para el traslado.");
    }
    
    // Crear la ruta para el transportador
    std::vector<ParadaRuta> ruta;
    // 1. Recoger de la bóveda de origen
    ruta.push_back({origen, TipoOperacion::RETIRO, solicitud});
    // 2. Entregar en la bóveda de destino
    ruta.push_back({destino, TipoOperacion::DEPOSITO, solicitud});

    // "Contratar" al transportador y asignarle la ruta
    transportador->asignarRuta(ruta);

    // En un sistema real, esto sería asíncrono. Aquí lo ejecutamos de inmediato.
    transportador->ejecutarRuta();

    // Registrar las operaciones a nivel del BCR
    // El retiro disminuye el saldo
    Registro reg_retiro(TipoOperacion::RETIRO, solicitud, origen, transportador);
    registrarOperacionBCR(reg_retiro);

    // El depósito aumenta el saldo
    Registro reg_deposito(TipoOperacion::DEPOSITO, solicitud, destino, transportador);
    registrarOperacionBCR(reg_deposito);
}

void Banco::registrarOperacionBCR(const Registro& reg) {
    libro_mayor.push_back(reg);
    if (reg.tipo == TipoOperacion::DEPOSITO || reg.tipo == TipoOperacion::INICIAL) {
        saldo_BCR += reg.monto_total;
    } else if (reg.tipo == TipoOperacion::RETIRO) {
        saldo_BCR -= reg.monto_total;
    }
    std::cout << "[BCR] Registro procesado. Saldo de control actualizado: " << saldo_BCR << "\n";
}

double Banco::totalEnBovedas() const {
    return std::accumulate(bovedas.begin(), bovedas.end(), 0.0,
        [](double sum, const auto& boveda_ptr) {
            return sum + boveda_ptr->total();
        });
}