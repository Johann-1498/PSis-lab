#pragma once
#include "OperacionException.h"
#include <string>

enum class CodigoActivo; // Forward declaration

class ActivosException : public OperacionException {
public:
    explicit ActivosException(const std::string& msg) : OperacionException("[Activos] " + msg) {}
};

class SaldoActivoInsuficienteException : public ActivosException {
public:
    SaldoActivoInsuficienteException(CodigoActivo cod, double req, double disp);
};

class DenominacionInvalidaException : public ActivosException {
public:
    DenominacionInvalidaException(double monto, const std::string& msg);
};

class ActivoNoExisteException : public ActivosException {
public:
    ActivoNoExisteException(const std::string& msg);
};