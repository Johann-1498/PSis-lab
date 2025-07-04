#pragma once
#include <string>
#include "Activos.h"

class Plaza;

class Boveda {
private:
    std::string codigo;
    Activos activos;
    Plaza* plaza;
public:
    Boveda(const std::string& codigo, Plaza* p);
    const std::string& getCodigo() const;
    void depositar(CodigoActivo cod, double monto);
    void retirar(CodigoActivo cod, double monto);
    void imprimirEstado() const;
};