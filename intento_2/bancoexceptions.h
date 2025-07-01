#pragma once
#include "OperacionException.h"
#include <string>

class BancoException : public OperacionException {
public:
    explicit BancoException(const std::string& message)
        : OperacionException("[Banco] " + message) {}
};

class BovedaNoEncontradaException : public BancoException {
public:
    explicit BovedaNoEncontradaException(const std::string& codigo)
        : BancoException("Bóveda no encontrada: " + codigo) {}
};

class SaldoInsuficienteException : public BancoException {
public:
    explicit SaldoInsuficienteException(const std::string& activo, double requerido, double disponible)
        : BancoException("Saldo insuficiente en " + activo + 
                        " (requerido: " + std::to_string(requerido) + 
                        ", disponible: " + std::to_string(disponible) + ")") {}
};