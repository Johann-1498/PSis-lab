#include "Banco.h"
#include "BancoExceptions.h"  
#include "CodigoActivo.h"  
#include "ActivosExceptions.h" 
#include "Plaza.h"
#include <iostream>
#include <numeric>

Banco::Banco(const std::string& nombre) : nombre(nombre), saldo_BCR(0.0) {}

void Banco::agregarBoveda(const std::string& codigo_boveda, Activos* a) {
    Boveda bov(codigo_boveda, a, this);
    bovedas.push_back(std::make_unique<Boveda>(bov));
}

Boveda* Banco::getBoveda(const std::string& codigo_boveda) {
    for (const auto& b : bovedas) {
        if (b->getCodigo() == codigo_boveda) {
            return b.get();
        }
    }
    throw BovedaNoEncontradaException(codigo_boveda);
}

void Banco::iniciarTrasladoInterbancario(Transportador* transportador) {
    std::cout << "- Banco " << this->nombre << "- Iniciando traslado desde " << transportador->getCodigo();
    std::cout << "\n======================================================\n";

    trasnportador.ejecutarRuta();
}

void Banco::registrarOperacionBCR(const Registro& reg) {
    registrosGenerales.push_back(reg);
    if (reg.tipo == TipoOperacion::DEPOSITO || reg.tipo) {
        saldo_BCR += reg.monto_total;
    } else if (reg.tipo == TipoOperacion::RETIRO) {
        saldo_BCR -= reg.monto_total;
    }
    std::cout << "Saldo BCR Registro procesado" << saldo_BCR << "\n";
}

double Banco::totalEnBovedas() const {
    return std::accumulate(bovedas.begin(), bovedas.end(), 0.0,
        [](double sum, const auto& boveda_ptr) {
            return sum + boveda_ptr->total();
        });
}

std::vector<Registro> Banco::consultarSaldosPorDia(const std::string& dia) const {
    std::vector<Registro> resultado;
    for (const auto& reg : registrosGenerales) {
        if (reg.dia == dia)
            resultado.push_back(reg);
    }
    return resultado;
}

std::vector<Registro> Banco::consultarSaldosPorMes(const std::string& mes) const {
    std::vector<Registro> resultado;
    for (const auto& reg : registrosGenerales) {
        if (reg.mes == mes)
            resultado.push_back(reg);
    }
    return resultado;
}