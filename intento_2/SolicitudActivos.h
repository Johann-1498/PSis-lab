#pragma once
#include <unordered_map>
#include "CodigoActivo.h"
#include "SolicitudActivosExceptions.h"
#include "String"
#include "TipoOperacion.h"
#include "Plaza.h"

struct SolicitudActivos {
    std::string dia, mes;
    std::unordered_map<CodigoActivo, double> activos;
    TipoOperacion tipo_op;

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