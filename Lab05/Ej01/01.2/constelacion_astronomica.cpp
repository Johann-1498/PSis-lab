#include "constelacion_astronomica.h"

static const ConstelacionAstronomica constelaciones[] = {
    {"Aries", 18, 4, 13, 5},
    {"Tauro", 14, 5, 19, 6},
    {"Géminis", 20, 6, 20, 7},
    {"Cancer", 21, 7, 9, 8},
    {"Leo", 10, 8, 15, 9},
    {"Virgo", 16, 9, 30, 10},
    {"Libra", 31, 10, 22, 11},
    {"Escorpio", 23, 11, 29, 11},
    {"Ofiuco", 30, 11, 17, 12}, 
    {"Sagitario", 18, 12, 18, 1},
    {"Capricornio", 19, 1, 15, 2},
    {"Acuario", 16, 2, 11, 3},
    {"Piscis", 12, 3, 17, 4}
};

const ConstelacionAstronomica* obtenerConstelacionesAstronomicas() {
    return constelaciones;
}

int cantidadConstelacionesAstronomicas() {
    return sizeof(constelaciones) / sizeof(ConstelacionAstronomica);
}