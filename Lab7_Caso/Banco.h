// Banco.h
#pragma once

#include <vector>
#include <algorithm>
#include "Plaza.h"
#include "Registro.h"
#include "Boveda.h"

class Transportador; // Declaración adelantada

class Banco {
private:
    Plaza plaza;
    std::vector<Boveda*> bovedas;
    std::vector<Transportador*> transportadoras;
    double saldo_BCR;
    std::vector<Registro> operaciones;

public:
    explicit Banco(const Plaza& p): plaza(p), saldo_BCR(0.0){}

    void registrarOperacion(const Registro& reg) {
        operaciones.push_back(reg);

        if (reg.tipo == TipoOperacion::DEPOSITO)
            saldo_BCR += reg.montoTotal;
        else if (reg.tipo == TipoOperacion::RETIRO)
            saldo_BCR -= reg.montoTotal;
    }

    void agregarBoveda(Boveda* b) {
        bovedas.push_back(b);
    }

    void agregarTransportador(Transportador* t) {
        transportadoras.push_back(t);
    }

    void deposito(Boveda* origen, Boveda* destino, const Boveda::SolicitudActivos& sol) {
        origen->transportar(*destino, sol);
        
        // Registrar operación en el banco
        Registro reg(TipoOperacion::TRASLADO, sol, &plaza, nullptr, this, this);
        registrarOperacion(reg);
    }
};