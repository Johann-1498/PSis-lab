#include "Boveda.h"
#include "Transportador.h" // Se necesita la definición completa aquí

Boveda::Boveda(const std::string& codigo_, Plaza* p)
  : codigo(codigo_), plaza(p) {
    if (!p) {
        throw std::invalid_argument("La bóveda debe pertenecer a una plaza.");
    }
}

void Boveda::depositar(const SolicitudActivos& sol, Transportador* t) {
    activos.depositar(sol);
    registrar(t ? TipoOperacion::DEPOSITO : TipoOperacion::INICIAL, sol, t);
}

void Boveda::retirar(const SolicitudActivos& sol, Transportador* t) {
    try {
        activos.retirar(sol);
        registrar(TipoOperacion::RETIRO, sol, t);
    } catch (const std::runtime_error& e) {
        // Convertimos excepciones estándar en nuestras excepciones específicas
        throw BovedaException(e.what());
    }
}

void Boveda::registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t) {
    registros.emplace_back(tipo, sol, this, t);
}

const std::vector<Registro>& Boveda::getRegistros() const {
    return registros;
}