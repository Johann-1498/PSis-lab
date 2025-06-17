#pragma once

struct Cancion {
    int id = 0;
    int cantidadEscuchas = 0;
    double sumaCalificaciones = 0.0;

    double obtenerPromedio() const {
        return cantidadEscuchas == 0 ? 0.0 : sumaCalificaciones / cantidadEscuchas;
    }

    bool operator<(const Cancion& otra) const {
        return this->obtenerPromedio() < otra.obtenerPromedio();
    }
};
