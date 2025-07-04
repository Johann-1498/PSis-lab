#pragma once
#include <unordered_map>
#include "CodigoActivo.h"
#include "SolicitudActivosExceptions.h"

struct SolicitudActivos {
    std::unordered_map<CodigoActivo, double> activos;

    bool empty() const {
        return activos.empty();
    }

    void validar() const {
        if (empty()) {
            throw SolicitudVaciaException();
        }

        for (const auto& item : activos) {
            if (item.second < 0) {
                throw MontoNegativoException(item.first, item.second);
            }
        }
    }
};