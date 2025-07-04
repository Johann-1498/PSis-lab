// Banco.h
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Boveda.h"
#include "Transportador.h"
#include "BancoExceptions.h"
#include "OperacionException.h"
#include "Plaza.h"

class Banco {
private:
    std::string nombre;
    std::vector<std::unique_ptr<Boveda>> bovedas;
    double saldo_BCR; // Saldo de control
    std::vector<Registro> registros; // Registro central del banco

public:
    explicit Banco(const std::string& nombre);
    const std::string& getNombre() const { return nombre; }

    void agregarBoveda(const std::string& codigo_boveda, Plaza* p);
    Boveda* getBoveda(const std::string& codigo_boveda);
    
    // Orquesta una operación de traslado
    void iniciarTrasladoInterbancario(
        Boveda* origen,
        Boveda* destino,
        Transportador* transportador,
        const SolicitudActivos& solicitud
    );

    void registrarOperacionBCR(const Registro& reg);
    double getSaldoBCR() const { return saldo_BCR; }
    double totalEnBovedas() const;
};