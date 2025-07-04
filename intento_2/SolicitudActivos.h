#pragma once
#include <unordered_map>
#include "CodigoActivo.h"
#include "SolicitudActivosExceptions.h"
#include "String"
#include "TipoOperacion.h"
#include "Plaza.h"
using namespace std;

struct SolicitudActivos {
    std::string dia, mes;
    std::unordered_map<CodigoActivo, std::unordered_map<std::search_n, int>> detalle_billetes;
    TipoOperacion tipo_op;

    bool empty() const {
        return detalle_billetes.empty();
    }


    void validar() const {
        if (empty()) {
            throw SolicitudVaciaException();
        }
        for (const auto& item : detalle_billetes) {
            int suma = 0;
            for (const auto& subitem : item.second) {
                if (subitem.second < 0) {
                    throw MontoNegativoException(item.first, subitem.second);
                }
                suma += subitem.second;
            }
            if (suma < 0) {
                throw MontoNegativoException(item.first, suma);
            }
        }
    }
};