#ifndef CALCULADORA_ZODIACO_H
#define CALCULADORA_ZODIACO_H

#include <string>

struct FechaNacimiento {
    int dia;
    int mes;
    int anio;
};

double calcularPosicionSolar(const FechaNacimiento& fecha);
std::string determinarSignoZodiacal(double grados_sol);

#endif