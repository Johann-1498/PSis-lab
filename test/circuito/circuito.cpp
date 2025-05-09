#include "circuito.h"
#include <iostream>
using namespace std;
Circuito::Circuito(float v) : tension(v) {}


Circuito::~Circuito() {
    eliminarResistencias();
}


void Circuito::setTension(float v) {
    tension = v;
}


void Circuito::agregarResistencia(float r) {
    resistencias.push_back(new Resistencia(r));
}


void Circuito::eliminarResistencias() {
    for (auto& r : resistencias) {
        delete r;
    }
    resistencias.clear();
}


float Circuito::calcularResistenciaSerie() const {
    float total = 0;
    for (const auto& r : resistencias) {
        total += r->getValor();
    }
    return total;
}
float Circuito::calcularResistenciaParalelo() const {
    if (resistencias.empty()) return 0;
   
    float inversoTotal = 0;
    for (const auto& r : resistencias) {
        if (r->getValor() != 0) {
            inversoTotal += 1.0f / r->getValor();
        }
    }
    return (inversoTotal == 0) ? 0 : 1.0f / inversoTotal;
}
float Circuito::calcularCorrienteSerie() const {
    if (resistencias.empty()) return 0;
    float req = calcularResistenciaSerie();
    return (req == 0) ? 0 : tension / req;
}
float Circuito::calcularCorrienteParalelo() const {
    if (resistencias.empty()) return 0;
    float req = calcularResistenciaParalelo();
    return (req == 0) ? 0 : tension / req;
}
void Circuito::mostrarResistencias() const {
    cout << "Resistencias en el circuito (" << resistencias.size() << "):" << endl;
    for (size_t i = 0; i < resistencias.size(); ++i) {
        cout << "R" << i+1 << ": " << resistencias[i]->getValor() << " Ω" << endl;
    }
}
void Circuito::mostrarResultados() const {
   
    if (resistencias.size() < 1) {
        cout << "\nDatos insuficientes." << endl;
        return;
    }
    cout << "\n=== Resultados del circuito ===" << endl;
    cout << "Tension aplicada: " << tension << " V" << endl;
    mostrarResistencias();
    cout << "\nEn configuracion SERIE:" << endl;
    cout << "Resistencia(R): " << calcularResistenciaSerie() << " Ω" << endl;
    cout << "Intensidad de Corriente(A): " << calcularCorrienteSerie() << " A" << endl;
    cout << "\nEn configuracion PARALELO:" << endl;
    cout << "Resistencia(R): " << calcularResistenciaParalelo() << " Ohmios Ω" << endl;
    cout << "Intensidad de Corriente(A): " << calcularCorrienteParalelo() << " A" << endl;
    cout << "=============================" << endl;
}
