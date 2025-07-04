// Transportador.h
#pragma once

#include <vector>
#include "Plaza.h"
#include "Registro.h"

class Transportador {
private:
    std::string nombre;
    std::string codigo;
    Plaza plaza;
    std::vector<Registro> cronograma;
public:
    Transportador(const std::string& n, const Plaza& p)
      : nombre(n), plaza(p)
    {}

    void programarOperacion(const Registro& reg) {
        cronograma.push_back(reg);
    }

    const std::vector<Registro>& obtenerCronograma() const {
        return cronograma;
    }

    void empezarPlaza(){
        for()
    }

};
