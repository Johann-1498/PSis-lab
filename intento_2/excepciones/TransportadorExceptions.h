#pragma once
#include "OperacionException.h"
#include <string>

class TransportadorException : public OperacionException {
public:
    explicit TransportadorException(const std::string& msg) : OperacionException("[Transportador] " + msg) {}
};

class RutaActivaException : public TransportadorException {
public:
    RutaActivaException();
};

class FalloEnRutaException : public TransportadorException {
public:
    FalloEnRutaException(const std::string& boveda_fallo, const std::string& motivo);
};