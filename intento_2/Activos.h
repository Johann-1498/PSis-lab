#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "CodigoActivo.h"  // Incluir el enum

#include "ActivosExceptions.h" // include exceptions activos

// ... (El código de Activo, Moneda, Bono, Joya, y Activos que proporcionaste va aquí, sin cambios)
// Tu código para Activos.h era funcional y completo para este escenario.
// Lo incluyo aquí para que la respuesta sea autocontenida.

/// Códigos de activ

class Activo {
public:
    virtual ~Activo() = default;
    virtual void depositar(double monto) = 0;
    virtual void retirar(double monto)  = 0;
    virtual double total() const        = 0;
};

class Moneda : public Activo {
public:
    explicit Moneda(CodigoActivo codigo)
      : codigo(codigo), valorTotal(0.0)
    {
        switch(codigo) {
            case CodigoActivo::SOLES:
                validos = {200,100,50,20,10};
                nombre = "Soles";
                break;
            case CodigoActivo::DOLARES:
                validos = {100,50,20,10,5,2,1};
                nombre = "Dolares";
                break;
            default:
                throw TipoMonedaInvalidoException(codigo);
        }
    }

    void depositar(double monto) override {
        if (monto < 0) {
            throw std::invalid_argument("Monto negativo no permitido");
        }
        valorTotal += monto;
    }

    void retirar(double monto) override {
        if (monto > valorTotal) {
            throw SaldoActivoInsuficienteException(codigo, monto, valorTotal);
        }
        valorTotal -= monto;
    }

    double total() const override {
        return valorTotal;
    }

private:
    CodigoActivo codigo;
    std::string nombre;
    double valorTotal;
    std::vector<int> validos;
    std::unordered_map<int,int> billetes;
};

class Bono : public Activo {
public:
    explicit Bono(double valorUnidad = 1.0)
      : unidades(0), valorUnidad(valorUnidad)
    {}
    void depositar(double monto) override {
        unidades += static_cast<int>(monto);
    }
    void retirar(double monto) override {
        int req = static_cast<int>(monto);
        if (req > unidades)
            throw std::runtime_error("Bonos insuficientes");
        unidades -= req;
    }
    double total() const override {
        return unidades * valorUnidad;
    }
private:
    int unidades;
    double valorUnidad;
};

class Joya : public Activo {
public:
    explicit Joya(double equivalencia = 1.0)
      : unidades(0), equivalencia(equivalencia)
    {}
    void depositar(double monto) override {
        unidades += static_cast<int>(monto);
    }
    void retirar(double monto) override {
        int req = static_cast<int>(monto);
        if (req > unidades)
            throw std::runtime_error("Joyas insuficientes");
        unidades -= req;
    }
    double total() const override {
        return unidades * equivalencia;
    }
private:
    int unidades;
    double equivalencia;
};

//-----------------------------Activos totales ----------------------------------------------------------------------
class Activos {
private:
    std::unordered_map<CodigoActivo, std::unique_ptr<Activo>> mapa;
public:
    Activos() {
        mapa[CodigoActivo::SOLES]   = std::make_unique<Moneda>(CodigoActivo::SOLES);
        mapa[CodigoActivo::DOLARES] = std::make_unique<Moneda>(CodigoActivo::DOLARES);
        mapa[CodigoActivo::BONO]    = std::make_unique<Bono>(1.0);
        mapa[CodigoActivo::JOYA]    = std::make_unique<Joya>(1.0);
    }

    void depositar(const std::unordered_map<CodigoActivo,double>& sol) {
        for (const auto& pair : sol) {
            CodigoActivo cod = pair.first;
            double m = pair.second;
            auto it = mapa.find(cod);
            if (it == mapa.end()) {
                throw ActivoNoExisteException(cod);
            }
            it->second->depositar(m);
        }
    }


    void retirar(const std::unordered_map<CodigoActivo,double>& sol) {
        // Transacción de prueba: verificar si todo se puede retirar antes de hacerlo
        for (const auto& pair : sol) {
            CodigoActivo cod = pair.first;
            double m = pair.second;
            auto it = mapa.find(cod);
            if (it == mapa.end())
                throw ActivoNoExisteException(cod);
            if (it->second->total() < m) {
                throw SaldoActivoInsuficienteException(cod, m, it->second->total());
            }
        }
        // Si todas las verificaciones pasan, proceder con el retiro
        for (const auto& pair : sol) {
            CodigoActivo cod = pair.first;
            double m = pair.second;
            mapa.find(cod)->second->retirar(m);
        }
    }

    double total() const {
        double suma = 0;
        for (const auto& it : mapa)
            suma += it.second->total();
        return suma;
    }
    
    // Método para obtener el total de un activo específico
    double totalPorActivo(CodigoActivo cod) const {
        auto it = mapa.find(cod);
        if (it != mapa.end()) {
            return it->second->total();
        }
        return 0.0;
    }
};