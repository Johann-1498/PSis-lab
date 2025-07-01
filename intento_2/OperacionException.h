#pragma once
#include <stdexcept>
#include <string>

// Clase base para todas las excepciones de operación bancaria
class OperacionException : public std::runtime_error {
public:
    explicit OperacionException(const std::string& message)
        : std::runtime_error("[OperacionException] " + message) {}
};

// Excepciones específicas para el Banco
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

// Excepciones específicas para el Transportador
class TransportadorException : public OperacionException {
public:
    explicit TransportadorException(const std::string& message)
        : OperacionException("[Transportador] " + message) {}
};

class RutaActivaException : public TransportadorException {
public:
    explicit RutaActivaException()
        : TransportadorException("El transportador ya tiene una ruta activa") {}
};

class RutaInvalidaException : public TransportadorException {
public:
    explicit RutaInvalidaException()
        : TransportadorException("La ruta asignada no es válida") {}
};

// Excepciones específicas para Bóveda
class BovedaException : public OperacionException {
public:
    explicit BovedaException(const std::string& message)
        : OperacionException("[Boveda] " + message) {}
};

class ActivoNoEncontradoException : public BovedaException {
public:
    explicit ActivoNoEncontradoException(CodigoActivo codigo)
        : BovedaException("Activo no encontrado: " + std::to_string(static_cast<int>(codigo))) {}
};