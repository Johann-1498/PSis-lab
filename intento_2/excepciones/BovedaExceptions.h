#pragma once
#include "OperacionException.h"
#include <string>

// Asumiendo que CodigoActivo está definido en otro lugar
enum class CodigoActivo; // Declaración forward

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