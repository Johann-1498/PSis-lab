#ifndef SIGNO_ZODIACAL_H
#define SIGNO_ZODIACAL_H

#include <string>

struct SignoZodiacal {
    std::string nombre;
    double inicio_grados;  
    double fin_grados;
};

const SignoZodiacal* obtenerSignosTradicionales();
int cantidadSignosTradicionales();

#endif