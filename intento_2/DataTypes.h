#pragma once
#include <string>

enum class CodigoActivo { SOLES, DOLARES, BONO, JOYA };
enum class TipoParada { RECOGER, ENTREGAR };

struct ParadaRuta {
    std::string codigo_boveda;
    TipoParada tipo;
    CodigoActivo codigo_activo;
    double monto;
};