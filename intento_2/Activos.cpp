#include "Activos.h"
#include "excepciones/ActivosExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>

SaldoActivoInsuficienteException::SaldoActivoInsuficienteException(CodigoActivo cod, double req, double disp)
    : ActivosException("Saldo insuficiente (requerido: " + std::to_string(req) + ", disponible: " + std::to_string(disp) + ")") {}
DenominacionInvalidaException::DenominacionInvalidaException(double monto, const std::string& msg)
    : ActivosException("Denominacion invalida para monto " + std::to_string(monto) + ". " + msg) {}
ActivoNoExisteException::ActivoNoExisteException(const std::string& msg)
    : ActivosException("Activo no existe: " + msg) {}

Moneda::Moneda(const std::vector<int>& denominaciones_validas) {
    for (int denom : denominaciones_validas) billetes[denom] = 0;
}

void Moneda::depositar(double monto) {
    if (monto < 0) throw DenominacionInvalidaException(monto, "Monto negativo no permitido.");
    int monto_int = static_cast<int>(monto);
    int monto_original = monto_int;
    for (auto it = billetes.rbegin(); it != billetes.rend(); ++it) {
        int denom = it->first;
        if (monto_int >= denom) {
            billetes[denom] += monto_int / denom;
            monto_int %= denom;
        }
    }
    if (monto_int != 0) throw DenominacionInvalidaException(monto, "No se pudo distribuir en billetes.");
    valorTotal += monto_original;
}

void Moneda::retirar(double monto) {
    if (monto < 0) throw DenominacionInvalidaException(monto, "Monto negativo no permitido.");
    if (monto > valorTotal) throw SaldoActivoInsuficienteException(CodigoActivo::SOLES, monto, valorTotal);
    valorTotal -= monto;
}

double Moneda::total() const { return valorTotal; }

void Moneda::imprimirDetalle() const {
    for (const auto& par : billetes) {
        if (par.second > 0) std::cout << "      - Billetes de " << std::setw(3) << par.first << ": " << par.second << std::endl;
    }
}

void Bono::depositar(double valor_bono) { items.push_back(valor_bono); }
void Bono::retirar(double valor_bono) {
    auto it = std::find(items.begin(), items.end(), valor_bono);
    if (it == items.end()) throw ActivoNoExisteException("Bono con valor " + std::to_string(valor_bono) + " no encontrado.");
    items.erase(it);
}
double Bono::total() const { return std::accumulate(items.begin(), items.end(), 0.0); }
void Bono::imprimirDetalle() const { std::cout << "      - Cantidad de Bonos: " << items.size() << std::endl; }

Activos::Activos() {
    mapa[CodigoActivo::SOLES] = std::make_unique<Moneda>(std::vector<int>{200, 100, 50, 20, 10});
    mapa[CodigoActivo::DOLARES] = std::make_unique<Moneda>(std::vector<int>{100, 50, 20, 10, 5, 2, 1});
    mapa[CodigoActivo::BONO] = std::make_unique<Bono>();
}

void Activos::depositar(CodigoActivo cod, double monto) { mapa.at(cod)->depositar(monto); }
void Activos::retirar(CodigoActivo cod, double monto) { mapa.at(cod)->retirar(monto); }
double Activos::totalPorActivo(CodigoActivo cod) const { return mapa.count(cod) ? mapa.at(cod)->total() : 0.0; }

double Activos::totalGeneral() const {
    double total = 0.0;
    for (const auto& par : mapa) {
        total += par.second->total();
    }
    return total;
}

void Activos::imprimirEstado() const {
    if (totalGeneral() < 0.01) {
        std::cout << "    (Vacío)\n";
        return;
    }
    for (const auto& par : mapa) {
        if (par.second->total() > 0) {
            par.second->imprimirDetalle();
        }
    }
    std::cout << "    --------------------------\n";
    std::cout << "    Total General: " << std::fixed << std::setprecision(2) << totalGeneral() << "\n";
}