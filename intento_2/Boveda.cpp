#include "Boveda.h"
#include "BovedaExceptions.h"
#include "CodigoActivo.h"
#include "ActivosExceptions.h"
#include "Transportador.h"
#include <stdexcept>

Boveda::Boveda(const std::string& codigo_, Plaza* p) 
    : codigo(codigo_), plaza(p) 
{
    if (p == nullptr) {
        throw std::invalid_argument("La bóveda debe pertenecer a una plaza válida.");
    }
}

void Boveda::depositar(const SolicitudActivos& sol, Transportador* t) {
    try {
        sol.validar();
        activos.depositar(sol);
        registrar(TipoOperacion::DEPOSITO, sol, t);
    } catch (const std::exception& e) {
        throw BovedaException(std::string("Error en depósito: ") + e.what());
    }
}

void Boveda::retirar(const SolicitudActivos& sol, Transportador* t) {
    try {
        sol.validar();  // Added validation for consistency
        activos.retirar(sol.activos);  // Fixed to use sol.activos
        registrar(TipoOperacion::RETIRO, sol, t);
    } catch (const std::exception& e) {
        throw BovedaException(std::string("Error en retiro: ") + e.what());
    }
}

void Boveda::registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t) {
    try {
        registros.emplace_back(tipo, sol, this, t);
    } catch (const std::exception& e) {
        throw BovedaException(std::string("Error al registrar operación: ") + e.what());
    }
}

const std::vector<Registro>& Boveda::getRegistros() const {
    return registros;
}