#ifndef CONSTELACION_ASTRONOMICA_H
#define CONSTELACION_ASTRONOMICA_H

#include <string>

struct ConstelacionAstronomica {
    std::string nombre;
    int diaInicio;
    int mesInicio;
    int diaFin;
    int mesFin;
};

const ConstelacionAstronomica* obtenerConstelacionesAstronomicas();
int cantidadConstelacionesAstronomicas();

#endif