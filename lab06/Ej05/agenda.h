#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Persona.h" 

class Agenda {
private:
    std::vector<Persona> fichas;
    static constexpr int MAX_FICHAS = 100;
    void cargarDatos();
    void guardarDatos() const;

public:
    Agenda();
    ~Agenda();
    void agregarPersona(const Persona& persona);
    void mostrarNombres() const;
    void mostrarDatosPersona(const std::string& nombre) const;
};

#endif
