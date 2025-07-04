#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "DataTypes.h" // Incluye CodigoActivo y otras definiciones compartidas

// NO DEBE HABER un '#include "Activos.h"' aquí

class Activo {
public:
    virtual ~Activo() = default;
    virtual void depositar(double monto) = 0;
    virtual void retirar(double monto) = 0;
    virtual double total() const = 0;
    virtual void imprimirDetalle() const = 0;
};

class Moneda : public Activo {
private:
    std::map<int, int> billetes;
    double valorTotal = 0.0;
public:
    explicit Moneda(const std::vector<int>& denominaciones_validas);
    void depositar(double monto) override;
    void retirar(double monto) override;
    double total() const override;
    void imprimirDetalle() const override;
};

class Bono : public Activo {
private:
    std::vector<double> items;
public:
    void depositar(double valor_bono) override;
    void retirar(double valor_bono) override;
    double total() const override;
    void imprimirDetalle() const override;
};

class Activos {
private:
    std::map<CodigoActivo, std::unique_ptr<Activo>> mapa;
public:
    Activos();
    void depositar(CodigoActivo cod, double monto);
    void retirar(CodigoActivo cod, double monto);
    double totalPorActivo(CodigoActivo cod) const;
    double totalGeneral() const;
    void imprimirEstado() const;
};