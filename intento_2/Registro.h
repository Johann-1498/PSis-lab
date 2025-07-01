#pragma once

#include <chrono>
#include "TipoOperacion.h"      // <-- Se incluye el archivo
#include "SolicitudActivos.h"   // <-- Se incluye el archivo

// EL ENUM 'TipoOperacion' YA NO ESTÁ AQUÍ. ¡ESTO ES LO CORRECTO!

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
        for (const auto& item : sol) {
            monto_total += item.second;
        }
    }
};