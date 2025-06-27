// Registro.h
#pragma once

#include <chrono>
#include <unordered_map>
#include "Activos.h"          
#include "Plaza.h"
#include "Transportador.h"
#include "Banco.h"

/// Tipos de operación que genera un registro
enum class TipoOperacion {
    RETIRO,
    DEPOSITO,
    TRASLADO,
    CANJE,
    PAGO
};

using SolicitudActivos = std::unordered_map<CodigoActivo,double>;

class Registro {
public:
    std::chrono::system_clock::time_point fecha;
    TipoOperacion tipo;
    SolicitudActivos solicitud;
    Plaza* plaza = nullptr;
    Transportador* transportador = nullptr;
    Banco* origen        = nullptr;
    Banco* destino       = nullptr;

    Registro(TipoOperacion tipo_, const SolicitudActivos& sol_, Plaza* pl = nullptr,Transportador* tr = nullptr,Banco* o = nullptr,
             Banco* d = nullptr)
      : fecha(std::chrono::system_clock::now())
      , tipo(tipo_)
      , solicitud(sol_)
      , plaza(pl)
      , transportador(tr)
      , origen(o)
      , destino(d)
    {}
};
