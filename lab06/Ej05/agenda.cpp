#include "Agenda.h"
#include <sstream>

Agenda::Agenda() {
    cargarDatos();
}

Agenda::~Agenda() {
    guardarDatos();
}

void Agenda::cargarDatos() {
    std::ifstream archivo("agenda.txt");
    if (!archivo) return;

    fichas.clear();
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre, direccion, telefono, email;
        short dia, mes, anio;

        std::getline(ss, nombre, '|');
        std::getline(ss, direccion, '|');
        std::getline(ss, telefono, '|');
        std::getline(ss, email, '|');
        ss >> dia >> mes >> anio;

        fichas.emplace_back(nombre, direccion, telefono, email, dia, mes, anio);
    }
}

void Agenda::guardarDatos() const {
    std::ofstream archivo("agenda.txt");
    for (const auto& p : fichas) {
        archivo << p.obtenerDatos() << std::endl;
    }
}

void Agenda::agregarPersona(const Persona& persona) {
    if (fichas.size() < MAX_FICHAS) {
        fichas.push_back(persona);
    } else {
        std::cout << "Agenda llena. No se pueden agregar mas fichas." << std::endl;
    }
}

void Agenda::mostrarNombres() const {
    for (const auto& p : fichas) {
        std::cout << p.nombre << std::endl;
    }
}

void Agenda::mostrarDatosPersona(const std::string& nombre) const {
    for (const auto& p : fichas) {
        if (p.nombre == nombre) {
            p.mostrarDatos();
            return;
        }
    }
    std::cout << "No se encontro una ficha con ese nombre." << std::endl;
}
