#pragma once
#include <unordered_map>
#include "Activos.h"
#include "SolicitudActivosExceptions.h" // Nuevo include

using SolicitudActivos = std::unordered_map<CodigoActivo, double>;

// Función de validación opcional
inline void validarSolicitud(const SolicitudActivos& sol) {
    if (sol.empty()) {
        throw SolicitudVaciaException();
    }
    
    for (const auto& item : sol) {
        if (item.second < 0) {
            throw MontoNegativoException(item.first, item.second);
        }
    }
}