#include <stdint.h>    // para tipos enteros de tamaño fijo
#include <stdbool.h>   // para bool
#include <stddef.h>    // para size_t
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>      // numeric_limits

using namespace std;

struct Equipo {
    string nombre;
    int vic = 0;
    int derrotas  = 0;

    virtual ~Equipo() = default;
    virtual void crearEquipo() = 0;    
    virtual void print() const = 0;
};

struct Baloncesto : Equipo {
    int perdidas = 0;
    int rebotes  = 0;
    string mejorAnotadorTriple;
    int triples  = 0;

    // Lee desde stdin todos los campos
    void crearEquipo() override {
        cout << "\n--- Datos de BALONCESTO ---\n";

        cout << "Nombre: ";
        getline(cin >> ws, nombre);          // limpia espacios y '\n'

        cout << "vic: ";
        cin >> vic;

        cout << "Derrotas: ";
        cin >> derrotas;

        cout << "Pérdidas de balón: ";
        cin >> perdidas;

        cout << "Rebotes: ";
        cin >> rebotes;

        cout << "Mejor anotador de triples: ";
        getline(cin >> ws, mejorAnotadorTriple);  // aquí también usamos ws

        cout << "Número de triples: ";
        cin >> triples;
    }


    void print() const override {
        cout
            << "\nBALONCESTO — " << nombre << "\n"
            << "  Vict.: " << vic
            << "  Der.: " << derrotas << "\n"
            << "  Pérdidas: " << perdidas
            << "  Rebotes: "   << rebotes << "\n"
            << "  Triplero: " << mejorAnotadorTriple
            << " (" << triples << " triples)\n";
    }
};

struct Futbol : Equipo {
    int empates   = 0;
    int golFavor  = 0;
    string goleador;
    int golesGole = 0;

    void crearEquipo() override {
        cout << "\n****************** Equipo de Futbol\n";

        cout << "Nombre: ";
        getline(cin >> ws, nombre);

        cout << "Victorias: ";
        cin >> vic;

        cout << "Derrotas: ";
        cin >> derrotas;

        cout << "Empates: ";
        cin >> empates;

        cout << "Goles a favor: ";
        cin >> golFavor;

        cout << "Goleador: ";
        getline(cin >> ws, goleador);

        cout << "Goles del goleador: ";
        cin >> golesGole;
    }

    void print() const override {
        cout
            << "\n-------------------- Equipo de Futbol" << nombre << "\n"
            << "  - Numero de victorias: " << vic
            << "  - Numero de derrotas: " << derrotas
            << "  - Numero de empate: " << empates << "\n"
            << "  - Goles a favor: " << golFavor << "\n"
            << "  - Goleador: " << goleador
            << "  - Goles del mejor goleador: " << golesGole << "\n";
    }
};

int main() {
    vector<unique_ptr<Equipo>> liga;
    int n;

    cout << "Numero de equipos de baloncesto de la liga: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        auto e = make_unique<Baloncesto>();
        e->crearEquipo();
        liga.push_back(move(e));
    }

    cout << "\nNumero de equipos de futbol de la liga: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        auto e = make_unique<Futbol>();
        e->crearEquipo();
        liga.push_back(move(e));
    }

    cout << "\n************ EQUIPOS DE LA LIGA ************\n";
    for (const auto& equipo : liga) {
        equipo->print();
    }

    return 0;
}