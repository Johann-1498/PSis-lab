#include "Boveda.h"
#include "BovedaExceptions.h"
#include "CodigoActivo.h"
#include "ActivosExceptions.h"
#include "Transportador.h"
#include <stdexcept>

Boveda::Boveda(const std::string& c, const Activos& a, const Banco& b): codigo(c), activos(a), banco(b){}

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
        sol.validar();  
        activos.retirar(sol.activos);  //Excepcion de saldo
        registrar(TipoOperacion::RETIRO, sol, t);
    } catch (const std::exception& e) {
        throw BovedaException(std::string("Error en retiro: ") + e.what());
    }
}

void Boveda::registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t) {//corregir
    try {
        Registro reg();
        registros.emplace_back(tipo, sol, this, t);//OBSERCADOOO
        this->banco.registrarOperacionBCR(reg);
    } catch (const std::exception& e) {
        throw BovedaException(std::string("Error al registrar operación: ") + e.what());
    }
}

const std::vector<Registro>& Boveda::getRegistros() const {
    return registros;
}