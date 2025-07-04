#pragma once
#include <chrono>
#include "DataTypes.h"

class Boveda;
class Transportador;

class Registro {
public:
    std::chrono::system_clock::time_point fecha;
    ParadaRuta detalle;
    Boveda* boveda_afectada;
    Transportador* transportador_implicado;

    Registro(const ParadaRuta& det, Boveda* boveda, Transportador* trans);
};