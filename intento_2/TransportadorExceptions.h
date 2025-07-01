#pragma once
#include "OperacionException.h"
#include <string>

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