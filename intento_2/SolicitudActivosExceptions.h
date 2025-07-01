#pragma once
#include "OperacionException.h"
#include "Activos.h" // Para CodigoActivo

class SolicitudActivosException : public OperacionException {
public:
    explicit SolicitudActivosException(const std::string& message)
        : OperacionException("[SolicitudActivos] " + message) {}
};

class SolicitudVaciaException : public SolicitudActivosException {
public:
    explicit SolicitudVaciaException()
        : SolicitudActivosException("La solicitud de activos está vacía") {}
};

class ActivoNoSoportadoException : public SolicitudActivosException {
public:
    explicit ActivoNoSoportadoException(CodigoActivo codigo)
        : SolicitudActivosException("Activo no soportado en solicitud: " + std::to_string(static_cast<int>(codigo))) {}
};

class MontoNegativoException : public SolicitudActivosException {
public:
    explicit MontoNegativoException(CodigoActivo codigo, double monto)
        : SolicitudActivosException("Monto negativo para activo " + 
                                  std::to_string(static_cast<int>(codigo)) + 
                                  ": " + std::to_string(monto)) {}
};