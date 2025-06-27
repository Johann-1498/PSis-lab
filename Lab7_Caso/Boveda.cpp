#include "Boveda.h"
#include <iostream>

Boveda::Boveda(const std::string& codigo_)
  : codigo(codigo_), activos(), registros() {}

SolicitudActivos Boveda::crearSolicitud() const {
    SolicitudActivos sol;
    double monto;

    std::cout << "Cantidad en Soles: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::SOLES] = monto;

    std::cout << "Cantidad en Dolares: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::DOLARES] = monto;

    std::cout << "Cantidad en Bonos: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::BONO] = monto;

    std::cout << "Cantidad en Joyas: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::JOYA] = monto;

    return sol;
}

void Boveda::depositar(const SolicitudActivos& sol) {
    activos.depositar(sol);
    registrarRegistro(TipoOperacion::DEPOSITO, sol);
}

void Boveda::retirar(const SolicitudActivos& sol) {
    activos.retirar(sol);
    registrarRegistro(TipoOperacion::RETIRO, sol);
}

void Boveda::transportar(const SolicitudActivos& sol) {
    activos.retirar(sol);
    activos.depositar(sol);
    registrarRegistro(TipoOperacion::TRASLADO, sol);
}

const std::vector<Registro>& Boveda::getRegistros() const {
    return registros;
}

void Boveda::registrarRegistro(TipoOperacion tipo, const SolicitudActivos& sol) {
    registros.emplace_back(tipo, sol);
}
