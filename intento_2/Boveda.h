#pragma once
#include <string>
#include <vector>
#include "Activos.h"
#include "Registro.h"
#include "OperacionException.h"
#include "Plaza.h"

class Boveda {
private:
    std::string codigo;
    Activos activos;
    std::vector<Registro> registros;
    Plaza* plaza;

    void registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t = nullptr);

public:
    explicit Boveda(const std::string& codigo, Plaza* p);
    const std::string& getCodigo() const { return codigo; }
    Plaza* getPlaza() const { return plaza; }
    
    void depositar(const SolicitudActivos& sol, Transportador* t = nullptr);
    void retirar(const SolicitudActivos& sol, Transportador* t = nullptr);
    
    double total() const { return activos.total(); }
    double totalPorActivo(CodigoActivo cod) const { return activos.totalPorActivo(cod); }

    const std::vector<Registro>& getRegistros() const;
};