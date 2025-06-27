// Boveda.h
#pragma once

#include <vector>
#include <stdexcept>
#include "Plaza.h"
#include "Registro.h"
#include "Activos.h"
#include "Transportador.h"
#include "Banco.h"


class Boveda {
private: 
    Banco banc ;
    const Plaza plaza;
    std::string codigo;
    double saldo;
    Activo activos;
    std::vector<Registro> s;
    std::vector<Transportador*> transportadores;
public:
    explicit Boveda(const Plaza& p)
      : plaza(p), saldo(0.0)
    {}

    void actualizarSaldoBCR() {
        saldo = activos.valorTotal();
    }

    bool verificarInventario(const Registro& reg) {
        return activos.verificarFondos(reg.monedas.front().getTipo(),static_cast<int>(reg.montoTotal));
    }

    void descontarInventario(const Registro& reg) {
        if (!verificarInventario(reg))
            throw std::runtime_error("Saldo insuficiente"); 
    }

    void incrementarInventario(const Registro& reg) {
        activos.agregarMoneda(reg.monedas.front());
    }

    void cargarArchivos(const Registro& /*reg*/) {
    }

    void registrar(const Registro& reg) {
        registro.push_back(reg);
    }

    
};
