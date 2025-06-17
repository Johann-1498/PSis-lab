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
};

class LSH {
private:
    int numHashes;
    int numCanciones;
    vector<vector<double>> planos;
    unordered_map<int, vector<int>> buckets;
    unordered_map<int, Usuario>* usuariosRef;

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

    double calcularDistanciaEuclidiana(const Usuario& usuario1, const Usuario& usuario2) {
        vector<int> vector1(numCanciones, 0);
        vector<int> vector2(numCanciones, 0);
        
        for (int cancion : usuario1.cancionesEscuchadas) {
            if (cancion < numCanciones) {
                vector1[cancion] = 1;
            }
        }
        
        for (int cancion : usuario2.cancionesEscuchadas) {
            if (cancion < numCanciones) {
                vector2[cancion] = 1;
            }
        }
        
        double suma = 0.0;
        for (int i = 0; i < numCanciones; ++i) {
            suma += pow(vector1[i] - vector2[i], 2);
        }
        
        return sqrt(suma);
    }

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
            if (comunes > 0) {
                double distancia = calcularDistanciaEuclidiana((*usuariosRef)[id], (*usuariosRef)[otro]);
                cout << "- Usuario " << otro << ": " << comunes << " canciones en comun, Distancia: " << distancia << "\n";
            }
        }

        if (candidatos.size() <= 1)
            cout << "(No se encontraron usuarios similares)\n";
    }

    double calcularDistanciaEntreUsuarios(int usuario1, int usuario2) {
        if (!usuariosRef->count(usuario1) || !usuariosRef->count(usuario2)) {
            throw runtime_error("Error en los usuarios.");
        }
        return calcularDistanciaEuclidiana((*usuariosRef)[usuario1], (*usuariosRef)[usuario2]);
    }

    vector<int> obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones = 10) {
        vector<int> recomendaciones;
        
        if (!usuariosRef->count(usuarioID)) {
            cout << "Usuario no encontrado.\n";
            return recomendaciones;
        }

        // 1 Encontrar usuarios similares
        int firma = calcularFirma((*usuariosRef)[usuarioID]);
        auto& candidatos = buckets[firma];

        // 2 recopilar canciones no escuchadas por el usuario
        unordered_map<int, int> cancionesCandidatas; // cancionID -> frecuencia
        const auto& cancionesUsuario = (*usuariosRef)[usuarioID].cancionesEscuchadas;

        for (int otroID : candidatos) {
            if (otroID == usuarioID) continue;
            
            for (int cancionID : (*usuariosRef)[otroID].cancionesEscuchadas) {
                if (!cancionesUsuario.count(cancionID)) {
                    cancionesCandidatas[cancionID]++;
                }
            }
        }

        //3ordenar por frecuencia (las más escuchadas por similares primero)
        vector<pair<int, int>> cancionesOrdenadas(
            cancionesCandidatas.begin(), cancionesCandidatas.end());
        
        // 4 seleccionar las mejores recomendaciones
        for (int i = 0; i < min(numRecomendaciones, (int)cancionesOrdenadas.size()); ++i) {
            recomendaciones.push_back(cancionesOrdenadas[i].first);
        }

        return recomendaciones;
    }

};