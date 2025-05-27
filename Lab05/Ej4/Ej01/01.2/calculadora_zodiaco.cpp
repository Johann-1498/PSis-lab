#include "calculadora_zodiaco.h"
#include "signo_zodiacal.h"
#include <cmath>
#include <ctime>

double calcularPosicionSolar(const FechaNacimiento& fecha) {
    // Convertir fecha a tiempo UNIX
    struct tm tm = {0};
    tm.tm_year = fecha.año - 1900;
    tm.tm_mon = fecha.mes - 1;
    tm.tm_mday = fecha.dia;
    time_t t = mktime(&tm);
    
    // Dias desde equinoccio de marzo 
    double dias_desde_equinoccio = difftime(t, 0) / 86400.0;
    
    // Posición ecliptica (0°-360°)
    double grados = fmod(dias_desde_equinoccio * 0.9856, 360.0);
    return (grados < 0) ? grados + 360.0 : grados;
}

std::string determinarSignoZodiacal(double grados_sol) {
    const SignoZodiacal* signos = obtenerSignosTradicionales();
    int total = cantidadSignosTradicionales();
    
    for (int i = 0; i < total; ++i) {
        if (grados_sol >= signos[i].inicio_grados && grados_sol <= signos[i].fin_grados) {
            return signos[i].nombre;
        }
    }
    return "Desconocido";
}