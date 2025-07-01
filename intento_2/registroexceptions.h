#pragma once
#include "OperacionException.h"
#include "TipoOperacion.h"

class RegistroException : public OperacionException {
public:
    explicit RegistroException(const std::string& message)
        : OperacionException("[Registro] " + message) {}
};

class RegistroInvalidoException : public RegistroException {
public:
    explicit RegistroInvalidoException(TipoOperacion tipo)
        : RegistroException("Operación inválida para registro: " + std::to_string(static_cast<int>(tipo))) {}
};

class RegistroMontoInvalidoException : public RegistroException {
public:
    explicit RegistroMontoInvalidoException(double monto)
        : RegistroException("Monto total inválido en registro: " + std::to_string(monto)) {}
};