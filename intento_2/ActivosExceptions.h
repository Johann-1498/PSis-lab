// ActivosExceptions.h
#pragma once
#include "OperacionException.h"
#include "CodigoActivo.h"  

class ActivosException : public OperacionException {
public:
    explicit ActivosException(const std::string& message)
        : OperacionException("-  Activos " + message) {}
};

class ActivoNoExisteException : public ActivosException {
public:
    explicit ActivoNoExisteException(CodigoActivo codigo)
        : ActivosException("Activo no existe: " + std::to_string(static_cast<int>(codigo))) {}
};

class SaldoActivoInsuficienteException : public ActivosException {
public:
    explicit SaldoActivoInsuficienteException(CodigoActivo codigo, double requerido, double disponible)
        : ActivosException("Saldo insuficiente para activo " + 
                          std::to_string(static_cast<int>(codigo)) + 
                          " (requerido: " + std::to_string(requerido) + 
                          ", disponible: " + std::to_string(disponible) + ")") {}
};

class TipoMonedaInvalidoException : public ActivosException {
public:
    explicit TipoMonedaInvalidoException(CodigoActivo codigo)
        : ActivosException("Código inválido para moneda: " + std::to_string(static_cast<int>(codigo))) {}
};