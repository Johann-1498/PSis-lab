#pragma once
#include <string>
#include <vector>
#include "Activos.h"
#include "Registro.h"
#include "OperacionException.h"
#include "Plaza.h"
#include "Banco.h"
using namespace std;

class Boveda {
private:
    string codigo;
    Activos activos;
    vector<Registro> registros;
    Banco banco;


public:

    explicit Boveda(const std::string& codigo, const Activos& a, const Banco& b);
    const string& getCodigo() const { return codigo; }
    
    void depositar(const SolicitudActivos& sol, Transportador* t);
    void retirar(const SolicitudActivos& sol, Transportador* t);
    
    double total() const { return activos.total(); }
    double totalPorActivo(CodigoActivo cod) const { return activos.totalPorActivo(cod); }

    const vector<Registro>& getRegistros() const;
    void registrar(TipoOperacion tipo, const SolicitudActivos& sol, Transportador* t);//Corregir

};