#pragma once

#include <chrono>
#include <vector>
#include "Activos.h"
#include "Plaza.h"
#include "Transportador.h"
#include "Banco.h"

class Registro {
public:
    std::chrono::system_clock::time_point fecha;
    TipoOperacion tipo;
    Activo activo;
    Plaza* plaza;
    Transportador* transportador = nullptr;
    Banco* origen = nullptr;
    Banco* destino = nullptr;
};
enum class TipoOperacion {
    RETIRO,
    DEPOSITO,
    TRASLADO,
    CANJE,
    PAGO
};
