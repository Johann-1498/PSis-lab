#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>

class Persona {
public:
    std::string nombre;
    std::string direccion;
    std::string telefono;
    std::string email;
    short dia_nacimiento;
    short mes_nacimiento;
    short anio_nacimiento;

    Persona(std::string nom, std::string dir, std::string tel, std::string mail, short dia, short mes, short anio);
    void mostrarDatos() const;
    
    std::string obtenerDatos() const;
};

#endif
