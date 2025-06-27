// Boveda.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Activos.h"
#include "Registro.h"

class Boveda {
private:
    std::string codigo;
    Activos activos;
    std::vector<Registro> registros;
    void registrarRegistro(TipoOperacion tipo, const SolicitudActivos& sol);

public:
    using SolicitudActivos = std::unordered_map<CodigoActivo,double>;

    explicit Boveda(const std::string& codigo_);

    SolicitudActivos crearSolicitud() const;
    void depositar(const SolicitudActivos& sol);
    void retirar(const SolicitudActivos& sol);
    void transportar(Boveda& destino, const SolicitudActivos& sol);

    const std::vector<Registro>& getRegistros() const;
};