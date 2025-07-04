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
    std::vector<Registro> registrosGenerales; // Registro central del banco
    std::vector<Transportador> trasnportadores;

public:
    explicit Banco(const std::string& nombre);
    const std::string& getNombre() const { return nombre; }

    void agregarBoveda(const std::string& codigo_boveda, Activos* p);
    Boveda* getBoveda(const std::string& codigo_boveda);
    
    void registrarOperacionBCR(const Registro& reg);
    double getSaldoBCR() const { return saldo_BCR; }
    double totalEnBovedas() const;
    std::vector<Registro> consultarSaldosPorDia(const std::string& dia) const;
    std::vector<Registro> consultarSaldosPorMes(const std::string& mes) const;
};
