#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <memory>

/// Códigos de activos
enum class CodigoActivo : int {
    SOLES   = 10,
    DOLARES = 11,
    BONO    = 20,
    JOYA    = 30
};

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
                throw std::invalid_argument("Código de moneda inválido");
        }
    }

    void depositar(double monto) override {
        distribuirEnBilletes(monto);
    }

    void retirar(double monto) override {
        if (monto > valorTotal)
            throw std::runtime_error("Saldo insuficiente en " + nombre);
        distribuirEnBilletes(-monto);
    }

    double total() const override {
        return valorTotal;
    }

    const std::unordered_map<int,int>& detalleBilletes() const {
        return billetes;
    }

private:
    CodigoActivo codigo;
    std::string nombre;
    double valorTotal;
    std::vector<int> validos;
    std::unordered_map<int,int> billetes;

    void distribuirEnBilletes(double monto) {
        double resto = monto;
        for (int denom : validos) {
            if (resto == 0.0) break;
            int disponibilidad = billetes[denom];
            int cuenta = static_cast<int>(resto) / denom;
            if (monto < 0) cuenta = std::min(cuenta, disponibilidad);
            if (cuenta == 0) continue;
            billetes[denom] += (monto < 0 ? -cuenta : cuenta);
            resto -= denom * cuenta;
        }
        if (resto != 0.0)
            throw std::runtime_error("No se puede distribuir exactamente " + std::to_string(monto) + " en " + nombre);
        valorTotal = 0;
        for (auto& [v,c] : billetes)
            valorTotal += v * c;
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
            throw std::runtime_error("Bono insuficiente");
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
            throw std::runtime_error("Joya insuficiente");
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

    //código/unidades
    void depositar(const std::unordered_map<CodigoActivo,double>& sol) {
        for (auto& [cod, m] : sol) {
            auto it = mapa.find(cod);
            if (it == mapa.end())
                throw std::invalid_argument("Activo no existe");
            it->second->depositar(m);
        }
    }

    void retirar(const std::unordered_map<CodigoActivo,double>& sol) {
        for (auto& [cod, m] : sol) {
            auto it = mapa.find(cod);
            if (it == mapa.end())
                throw std::invalid_argument("Activo no existe");
            it->second->retirar(m);
        }
    }

    double total() const {
        double suma = 0;
        for (auto& [_, ptr] : mapa)
            suma += ptr->total();
        return suma;
    }
};
