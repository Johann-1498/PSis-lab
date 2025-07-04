#include "Registro.h"

Registro::Registro(const ParadaRuta& det, Boveda* boveda, Transportador* trans)
    : fecha(std::chrono::system_clock::now()),
      detalle(det),
      boveda_afectada(boveda),
      transportador_implicado(trans) {}