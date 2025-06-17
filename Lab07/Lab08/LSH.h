// Archivo: LSH.h
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include "RankingCanciones.h"

using namespace std;

struct Usuario {
    int id;
    unordered_set<int> cancionesEscuchadas;
    // Opcional: se podría usar vector<Cancion*> si deseas referencia directa a objetos
};

class LSH { // Nombre de clase corregido
private:
    int numHashes;
    int numCanciones;
    vector<vector<double>> planos;
    unordered_map<int, vector<int>> buckets;
    unordered_map<int, Usuario>* usuariosRef;

public:
    LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios)
        : numHashes(hashes), numCanciones(totalCanciones), usuariosRef(&usuarios) {
        generarPlanos();
        construirBuckets();
    }

    void buscarSimilares(int id) {
        if (!usuariosRef->count(id)) {
            cout << "Usuario no encontrado.\n";
            return;
        }

        int firma = calcularFirma((*usuariosRef)[id]);
        auto& candidatos = buckets[firma];

        cout << "\nUsuarios similares a " << id << ":\n";
        for (int otro : candidatos) {
            if (otro == id) continue;
            int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro]);
            if (comunes > 0)
                cout << "- Usuario " << otro << " con " << comunes << " canciones en comun\n";
        }

        if (candidatos.size() <= 1)
            cout << "(No se encontraron usuarios similares)\n";
    }

private:
    void generarPlanos() {
        mt19937 gen(random_device{}());
        normal_distribution<double> dist(0.0, 1.0);
        planos.resize(numHashes, vector<double>(numCanciones));
        for (int i = 0; i < numHashes; ++i)
            for (int j = 0; j < numCanciones; ++j)
                planos[i][j] = dist(gen);
    }

    void construirBuckets() {
        for (const auto& [id, user] : *usuariosRef) {
            int firma = calcularFirma(user);
            buckets[firma].push_back(id);
        }
    }

    int calcularFirma(const Usuario& u) {
        int firma = 0;
        for (int i = 0; i < numHashes; ++i) {
            double suma = 0.0;
            for (int c : u.cancionesEscuchadas)
                if (c < numCanciones)
                    suma += planos[i][c];
            if (suma > 0)
                firma |= (1 << i);
        }
        return firma;
    }

    int contarEnComun(const Usuario& a, const Usuario& b) {
        int comunes = 0;
        for (int c : a.cancionesEscuchadas)
            if (b.cancionesEscuchadas.count(c))
                ++comunes;
        return comunes;
    }
};
