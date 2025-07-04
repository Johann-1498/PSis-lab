#include "Boveda.h"
#include <iostream>

Boveda::Boveda(const std::string& codigo, Plaza* p) : codigo(codigo), plaza(p) {}
const std::string& Boveda::getCodigo() const { return codigo; }
void Boveda::depositar(CodigoActivo cod, double monto) { activos.depositar(cod, monto); }
void Boveda::retirar(CodigoActivo cod, double monto) { activos.retirar(cod, monto); }
void Boveda::imprimirEstado() const { activos.imprimirEstado(); }