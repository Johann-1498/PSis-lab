#pragma once
#include "ExcepcionBancaria.h"

class ExcepcionSaldoInsuficiente : public ExcepcionBancaria {
    int bovedaID;
    double saldoDisponible;
    double saldoRequerido;
    string moneda;

public:
    ExcepcionSaldoInsuficiente(int bovedaID, double disponible, double requerido,
                                string moneda, int operacionID = -1)
        : ExcepcionBancaria("ExcepcionSaldoInsuficiente",
                            "Saldo insuficiente en bóveda",
                            "ERR_SALDO", false,
                            "Verifique los fondos antes de continuar.",
                            Severidad::ALTA, operacionID),
          bovedaID(bovedaID), saldoDisponible(disponible),
          saldoRequerido(requerido), moneda(moneda) {}

    string descripcion() const override {
        ostringstream oss;
        oss << ExcepcionBancaria::descripcion()
            << " [Bóveda: " << bovedaID << "] "
            << "[Disponible: " << saldoDisponible << " " << moneda << "] "
            << "[Requerido: " << saldoRequerido << "]";
        return oss.str();
    }
};
