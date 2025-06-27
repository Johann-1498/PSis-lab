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
    std::vector<Registro> calendario;
public:
    Transportador(const std::string& n, const Plaza& p)
      : nombre(n), plaza(p)
    {}

    void programarEntrega(const Registro& reg) {
        calendario.push_back(reg);
    }

    void programarRecogida(const Registro& reg) {
        calendario.push_back(reg);
    }

    const std::vector<Registro>& obtenerCalendario() const {
        return calendario;
    }


};
