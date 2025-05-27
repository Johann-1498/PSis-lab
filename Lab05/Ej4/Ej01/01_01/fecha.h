#ifndef FECHA_H
#define FECHA_H

// Declaración de la estructura Fecha
struct Fecha {
    int dia;
    int mes;
    int anio;
};

// Declaraciones de funciones
bool esBisiesto(int anio);
int diasEnMes(int mes, int anio);
bool fechaValida(Fecha fecha);
long fechaADias(Fecha fecha);
long diferenciaDias(Fecha fecha1, Fecha fecha2);

#endif