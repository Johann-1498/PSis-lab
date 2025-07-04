#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include "CodigoActivo.h"
#include "SolicitudActivos.h"
#include "ActivosExceptions.h" 

class Activo {
    protected:
        CodigoActivo codigo;
    public:
        virtual ~Activo() = default;
        virtual void depositar(double monto) = 0;
        virtual void retirar(double monto)  = 0;
        virtual double total() const        = 0;
};

class Moneda : public Activo {
private:
    std::string tipo;
    double valorTotal;
    std::vector<int> validos; 
    std::unordered_map<int,int> billetes;
public:
    explicit Moneda(CodigoActivo c)
    {
        this->codigo=c;
        this->valorTotal=0;

        switch(codigo) {
            case CodigoActivo::SOLES:
                validos = {200,100,50,20,10};
                tipo = "Soles";
                break;
            case CodigoActivo::DOLARES:
                validos = {100,50,20,10,5,2,1};
                tipo = "Dolares";
                break;
            default:
                throw TipoMonedaInvalidoException(codigo);
        }
    }

    void depositar(const std::unordered_map<int, int>& map_billetes) {
        double subtotal = 0;
        for (const auto& par : map_billetes) {
            int denom = par.first;
            int cant  = par.second;
            if (std::find(validos.begin(), validos.end(), denom) == validos.end())
                throw std::invalid_argument("Denominación no válida para " + tipo);
            billetes[denom] += cant;
            subtotal += denom * cant;
        }
        valorTotal += subtotal;
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

    void depositar(const SolicitudActivos& sol) {
        sol.validar(); // Valida

        for (const auto& par : sol.detalle_billetes) {
            CodigoActivo cod = par.first;
            const auto& detalle = par.second;//billetes de la solicitud

            auto it = mapa.find(cod);
            if (it == mapa.end()) {
                throw ActivoNoExisteException(cod);
            }
            //Monedas
            if (cod == CodigoActivo::SOLES || cod == CodigoActivo::DOLARES) {
                std::unordered_map<int, int> detalle_int;
                for (const auto& sub : detalle) {
                    int denominacion = std::stoi(sub.first); // string a int
                    int cantidad = sub.second;
                    detalle_int[denominacion] = cantidad;
                }
                Moneda* moneda = dynamic_cast<Moneda*>(it->second.get());
                if (!moneda)
                    throw std::invalid_argument("Solo moneda acepta desglose de billetes");
                moneda->depositar(detalle_int);
            } else {
                // Para joyas y bonos
                int total = 0;
                for (const auto& sub : detalle)
                    total += sub.second;
                it->second->depositar(static_cast<double>(total));
            }
        }
    }


    void retirar(const std::unordered_map<CodigoActivo,double>& sol) {
        // Transacción de prueba: verificar si todo se puede retirar antes de hacerlo
        for (const auto& par : sol) {
            CodigoActivo cod = par.first;
            double m = par.second;
            auto it = mapa.find(cod);
            if (it == mapa.end())
                throw ActivoNoExisteException(cod);
            if (it->second->total() < m) {
                throw SaldoActivoInsuficienteException(cod, m, it->second->total());
            }
        }

        // se retiran
        for (const auto& par : sol) {
            CodigoActivo cod = par.first;
            double m = par.second;
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