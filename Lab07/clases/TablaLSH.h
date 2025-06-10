#ifndef TABLA_LSH_H
#define TABLA_LSH_H

#include <vector>
#include <unordered_map>
#include <random>
#include "UsuarioDisperso.h"

// tabla lsh adaptada para vectores dispersos - no desperdicia memoria en ceros
struct TablaLSHDispersa {
    int numHashes;
    int numCancionesTotal;
    std::vector<std::vector<double>> planos; // numHashes x numCancionesTotal
    std::unordered_map<int, std::vector<int>> buckets; // hash -> lista de usuarios
    
    TablaLSHDispersa(int numHashes_, int numCancionesTotal_, std::mt19937 &gen)
        : numHashes(numHashes_), numCancionesTotal(numCancionesTotal_) {
        
        // generar planos aleatorios para lsh usando distribucion normal
        std::normal_distribution<double> dist(0.0, 1.0);
        planos.resize(numHashes, std::vector<double>(numCancionesTotal_));
        for(int i = 0; i < numHashes; ++i) {
            for(int j = 0; j < numCancionesTotal_; ++j) {
                planos[i][j] = dist(gen);
            }
        }
    }
    
    // calcula la firma lsh usando solo las canciones que el usuario escucho
    // esto es mucho mas eficiente que multiplicar por ceros
    int firmaDispersa(const UsuarioDisperso &usuario) const {
        int id = 0;
        for(int i = 0; i < numHashes; ++i) {
            double producto = 0.0;
            // solo considerar canciones que el usuario escucho
            for(auto &par : usuario.canciones) {
                int cancionID = par.first;
                double calificacion = par.second;
                if(cancionID < numCancionesTotal) {
                    producto += planos[i][cancionID] * calificacion;
                }
            }
            // si el producto es positivo, poner un 1 en esa posicion del hash
            if(producto > 0) id |= (1 << i);
        }
        return id;
    }
};

#endif