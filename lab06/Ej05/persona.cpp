#include "Persona.h"
#include <iostream>

Persona::Persona(std::string nom, std::string dir, std::string tel, std::string mail, short dia, short mes, short anio)
    : nombre(nom), direccion(dir), telefono(tel), email(mail), dia_nacimiento(dia), mes_nacimiento(mes), anio_nacimiento(anio) {}

void Persona::mostrarDatos() const {
    std::cout << "Nombre: " << nombre << "\nDireccion: " << direccion << "\nTelefono: " << telefono
              << "\nEmail: " << email << "\nFecha de nacimiento: " << dia_nacimiento << "/" << mes_nacimiento << "/" << anio_nacimiento << std::endl;
}

std::string Persona::obtenerDatos() const {
    return nombre + "|" + direccion + "|" + telefono + "|" + email + "|" + 
           std::to_string(dia_nacimiento) + "|" + std::to_string(mes_nacimiento) + "|" + std::to_string(anio_nacimiento);
}
