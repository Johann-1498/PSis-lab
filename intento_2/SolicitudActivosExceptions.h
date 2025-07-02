#pragma once
#include <stdexcept>
#include "CodigoActivo.h"

class SolicitudActivosException : public std::runtime_error {
public:
    explicit SolicitudActivosException(const std::string& message)
        : std::runtime_error("[SolicitudActivos] " + message) {}
};

class SolicitudVaciaException : public SolicitudActivosException {
public:
    SolicitudVaciaException()
        : SolicitudActivosException("La solicitud está vacía") {}
};

class MontoNegativoException : public SolicitudActivosException {
public:
    MontoNegativoException(CodigoActivo codigo, double monto)
        : SolicitudActivosException("Monto negativo no permitido para " +
                                    std::to_string(static_cast<int>(codigo)) +
                                    ": " + std::to_string(monto)) {}
};
