#pragma once
#include <chrono>
#include "TipoOperacion.h"
#include "SolicitudActivos.h"
#include "RegistroExceptions.h"

// Forward declarations
class Boveda;
class Transportador;

class Registro {
public:
    const std::chrono::system_clock::time_point fecha;
    const TipoOperacion tipo;
    const SolicitudActivos solicitud;
    Boveda* const boveda_afectada;
    Transportador* const transportador;
    const double monto_total;

    Registro(TipoOperacion tipo_, const SolicitudActivos& sol, Boveda* boveda, Transportador* trans = nullptr)
      : fecha(std::chrono::system_clock::now()),
        tipo(tipo_),
        solicitud(sol),
        boveda_afectada(boveda),
        transportador(trans),
        monto_total(calculateTotal(sol))
    {
        validateInput(sol);
    }

private:
    void validateInput(const SolicitudActivos& sol) const {
        sol.validar(); // Use SolicitudActivos's validation
    }

    double calculateTotal(const SolicitudActivos& sol) const {
        double total = 0.0;
        for (const auto& item : sol.activos) {
            total += item.second;
        }
        
        if (total <= 0) {
            throw RegistroMontoInvalidoException(total);
        }
        return total;
    }
};