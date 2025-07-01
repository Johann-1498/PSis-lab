#pragma once
#include <chrono>
#include "TipoOperacion.h"
#include "SolicitudActivos.h"
#include "RegistroExceptions.h" // Nuevo include

// Forward declarations
class Plaza;
class Transportador;
class Banco;
class Boveda;

class Registro {
public:
    std::chrono::system_clock::time_point fecha;
    TipoOperacion tipo;
    SolicitudActivos solicitud;
    Boveda* boveda_afectada = nullptr;
    Transportador* transportador = nullptr;
    double monto_total = 0.0;

    Registro(TipoOperacion tipo_, const SolicitudActivos& sol, Boveda* boveda, Transportador* trans = nullptr)
      : fecha(std::chrono::system_clock::now()),
        tipo(tipo_),
        solicitud(sol),
        boveda_afectada(boveda),
        transportador(trans)
    {
        if (sol.empty()) {
            throw SolicitudVaciaException();
        }
        
        for (const auto& item : sol) {
            if (item.second < 0) {
                throw MontoNegativoException(item.first, item.second);
            }
            monto_total += item.second;
        }
        
        if (monto_total <= 0) {
            throw RegistroMontoInvalidoException(monto_total);
        }
    }
};