// Activos.h
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

static constexpr int COD_SOLES   = 10;
static constexpr int COD_DOLARES = 11;
static constexpr int COD_BONO    = 20;
static constexpr int COD_JOYA    = 30;

class Activo {
protected:
    std::string nombre;
    double valor;

public:
    explicit Activo(const std::string& nombre_): nombre(nombre_), valor(0.0) {}
    virtual ~Activo() = default;

    virtual void calcularTotal() = 0;
};

class Moneda : public Activo {
private:
    std::unordered_map<int,int> billetes;
    std::vector<int>            validos;

public:

    explicit Moneda(const std::string& tipoMoneda): Activo(tipoMoneda){
        if (nombre == "Soles") {
            validos = {10, 20, 50, 100, 200};
        } else if (nombre == "Dolares") {
            validos = {1, 2, 5, 10, 20, 50, 100};
        } else {
            throw std::invalid_argument("Moneda desconocida: " + nombre);
        }
    }

    void agregarMonto(int valor, int cantidad) {
        if (std::find(validos.begin(), validos.end(), valor) == validos.end()) {
            throw std::invalid_argument("Denominación inválida para " + nombre);
        }
        billetes[valor] += cantidad;
        calcularTotal();
    }

    /// Retira monto si hay suficiente (por denominación)
    void retirarMonto(int valor, int cantidad) {
        auto it = billetes.find(valor);
        if (it == billetes.end() || it->second < cantidad) {
            throw std::runtime_error("Fondos insuficientes en " + nombre);
        }
        it->second -= cantidad;
        calcularTotal();
    }

    /// Devuelve el total acumulado
    double obtenerTotal() const {
        return valor;
    }

    /// Suma todos los billetes y actualiza valor
    void calcularTotal() override {
        double suma = 0;
        for (auto& [v, c] : billetes) {
            suma += v * c;
        }
        valor = suma;
    }
};

/// Activo de tipo Bono: valor fijo
class Bono : public Activo {
public:
    Bono(const std::string& tipoBono, double valorNominal)
      : Activo(tipoBono)
    {
        valor = valorNominal;
    }

    void calcularTotal() override {
        // no-op: valor ya fijado
    }
};

/// Activo de tipo Joya: valor fijo
class Joya : public Activo {
public:
    Joya(const std::string& nombreJoya, double equivalencia)
      : Activo(nombreJoya)
    {
        valor = equivalencia;
    }

    void calcularTotal() override {
        // no-op: valor ya fijado
    }
};

/// Solicitud de activos: clave=código de activo, valor=cantidad a operar
using SolicitudActivos = std::unordered_map<int,int>;

/// Contenedor de todos los activos de una bóveda
class Activos {
private:
    Moneda               soles;
    Moneda               dolares;
    std::vector<Bono>    bonos;
    std::vector<Joya>    joyas;

public:
    Activos()
      : soles("Soles"), dolares("Dolares") {}

    /**
     * Deposita activos según código y cantidad:
     * - COD_SOLES/COD_DOLARES: suma billetes de valor 1 por cantidad indicada
     * - COD_BONO: agrega <cantidad> bonos genéricos (valorNominal=0)
     * - COD_JOYA: agrega <cantidad> joyas genéricas (equivalencia=0)
     */
    void depositar(const SolicitudActivos& sol) {
        for (auto& [codigo, cantidad] : sol) {
            switch (codigo) {
                case COD_SOLES:
                    soles.agregarMonto(1, cantidad);
                    break;
                case COD_DOLARES:
                    dolares.agregarMonto(1, cantidad);
                    break;
                case COD_BONO:
                    for (int i = 0; i < cantidad; ++i)
                        bonos.emplace_back("Bono", 0.0);
                    break;
                case COD_JOYA:
                    for (int i = 0; i < cantidad; ++i)
                        joyas.emplace_back("Joya", 0.0);
                    break;
                default:
                    throw std::invalid_argument("Código de activo desconocido");
            }
        }
    }

    /**
     * Retira activos según solicitud:
     * - COD_SOLES/COD_DOLARES: resta billetes de valor 1 por cantidad indicada
     * - COD_BONO: elimina <cantidad> bonos del vector (si existen)
     * - COD_JOYA: elimina <cantidad> joyas del vector (si existen)
     */
    void retirar(const SolicitudActivos& sol) {
        for (auto& [codigo, cantidad] : sol) {
            switch (codigo) {
                case COD_SOLES:
                    soles.retirarMonto(1, cantidad);
                    break;
                case COD_DOLARES:
                    dolares.retirarMonto(1, cantidad);
                    break;
                case COD_BONO:
                    for (int i = 0; i < cantidad && !bonos.empty(); ++i)
                        bonos.pop_back();
                    break;
                case COD_JOYA:
                    for (int i = 0; i < cantidad && !joyas.empty(); ++i)
                        joyas.pop_back();
                    break;
                default:
                    throw std::invalid_argument("Código de activo desconocido");
            }
        }
    }

    /// Valor total combinado de todos los activos
    double total() const {
        double suma = soles.obtenerTotal() + dolares.obtenerTotal();
        for (const auto& b : bonos)   suma += b.valor;
        for (const auto& j : joyas)   suma += j.valor;
        return suma;
    }
};
