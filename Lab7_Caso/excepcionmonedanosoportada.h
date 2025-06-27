#pragma once
#include "ExcepcionBancaria.h"
#include <vector>

class ExcepcionMonedaNoSoportada : public ExcepcionBancaria {
    int bovedaID;
    string monedaSolicitada;
    vector<string> monedasSoportadas;

public:
    ExcepcionMonedaNoSoportada(int bovedaID, string solicitada,
                                vector<string> soportadas, int operacionID = -1)
        : ExcepcionBancaria("ExcepcionMonedaNoSoportada",
                            "Moneda solicitada no es soportada",
                            "ERR_MONEDA", false,
                            "Cambie a una moneda soportada por la bóveda",
                            Severidad::MEDIA, operacionID),
          bovedaID(bovedaID), monedaSolicitada(solicitada),
          monedasSoportadas(soportadas) {}

    string descripcion() const override {
        ostringstream oss;
        oss << ExcepcionBancaria::descripcion()
            << " [Bóveda: " << bovedaID << "] "
            << "[Solicitada: " << monedaSolicitada << "] "
            << "[Soportadas: ";
        for (const auto& m : monedasSoportadas) oss << m << " ";
        oss << "]";
        return oss.str();
    }
};
