#pragma once
#include <unordered_map>
#include "CodigoActivo.h"
#include "SolicitudActivosExceptions.h"

struct SolicitudActivos {
    std::unordered_map<CodigoActivo, double> activos;

    void validar() const {
        if (activos.empty()) {
            throw SolicitudVaciaException();
        }

        for (const auto& item : activos) {
            if (item.second < 0) {
                throw MontoNegativoException(item.first, item.second);
            }
        }
    }
};
