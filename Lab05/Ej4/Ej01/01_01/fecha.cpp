#include "fecha.h"
#include <stdexcept>

// Implementación de funciones

bool esBisiesto(int anio) {
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
        return true;
    }
    return false;
}

int diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return esBisiesto(anio) ? 29 : 28;
        default:
            throw std::invalid_argument("Mes inválido");
    }
}

bool fechaValida(Fecha fecha) {
    if (fecha.mes < 1 || fecha.mes > 12) {
        return false;
    }
    if (fecha.dia < 1 || fecha.dia > diasEnMes(fecha.mes, fecha.anio)) {
        return false;
    }
    return true;
}

long fechaADias(Fecha fecha) {
    if (!fechaValida(fecha)) {
        throw std::invalid_argument("Fecha inválida");
    }
    
    long totalDias = 0;
    
    // Sumar dias de los años completos anteriores
    for (int anio = 1; anio < fecha.anio; anio++) {
        totalDias += esBisiesto(anio) ? 366 : 365;
    }
    
    // Sumar dias de los meses completos anteriores en el año actual
    for (int mes = 1; mes < fecha.mes; mes++) {
        totalDias += diasEnMes(mes, fecha.anio);
    }
    
    // Sumar dias del mes actual
    totalDias += fecha.dia;
    
    return totalDias;
}

long diferenciaDias(Fecha fecha1, Fecha fecha2) {
    long dias1 = fechaADias(fecha1);
    long dias2 = fechaADias(fecha2);
    return dias2 - dias1;
}