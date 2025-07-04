#pragma once
#include <string>
#include <vector>
#include "Activos.h"
#include "Registro.h"
#include "OperacionException.h"
#include "Plaza.h"
using namespace std;

class Boveda {
private:
    string codigo;
    Activos activos;
    vector<Registro> registros;

    void registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t);

public:
    explicit Boveda(const string& codigo, Plaza* p);
    const string& getCodigo() const { return codigo; }
    
    void depositar(const SolicitudActivos& sol, Transportador* t);
    void retirar(const SolicitudActivos& sol, Transportador* t);
    
    double total() const { return activos.total(); }
    double totalPorActivo(CodigoActivo cod) const { return activos.totalPorActivo(cod); }

    const vector<Registro>& getRegistros() const;
};