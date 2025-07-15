#include "LSH.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <random>

#include <thread>
#include <vector>
#include <iostream>


using namespace std;

LSH::LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios)
    : numHashes(hashes), numCanciones(totalCanciones), usuariosRef(&usuarios) {
    generarPlanos();
    calcularFirma();   
    construirBuckets(); 
}

void LSH::generarPlanos() {

    //planos.resize(numHashes, vector<double>(numCanciones));
    planos.assign(numHashes, vector<double>(numCanciones));

    int nHilos = 16;
    int rango =  (numHashes + nHilos - 1) / nHilos; //rango que procesara cada hilo
    
    vector<thread> hilos;
    hilos.reserve(nHilos);

    int inicio = 0, fin = 0;
    
    for(int k = 0; k < nHilos; ++k){
        inicio = k*rango;
        fin = min(inicio + rango, numHashes);
        hilos.emplace_back([this, inicio, fin]() {

            mt19937 gen(random_device{}());
            normal_distribution<double> dist(0.0, 1.0);
            for (int i = inicio; i < fin; ++i) {
                for (int j = 0; j < numCanciones; ++j) {
                    planos[i][j] = dist(gen);
                }
            }
        });   
    }
    
    for (auto& h : hilos) {//terminan los hilos
        h.join();
    } 
    
}

void LSH::construirBuckets() {
    unsigned int nHilos = 16;  
    int rango = (usuariosRef->size() + nHilos - 1) / nHilos;

    vector<thread> hilos;
    hilos.reserve(nHilos);

    int inicio = 0, fin = 0;
    auto it = usuariosRef->begin();
    for (unsigned int t = 0; t < nHilos; ++t) {
        inicio = t * rango;
        fin = min(inicio + rango, (int)usuariosRef->size());

        hilos.emplace_back([this, inicio, fin, &it]() {
            for (int i = inicio; i < fin; ++i) {
                int firma = it->second.firma;  // Usamos la firma ya calculada
                buckets[firma].push_back(it->first);
                ++it;  // Avanzamos en el mapa
            }
        });
    }

    // Esperamos a que todos los hilos terminen
    for (auto& h : hilos) {
        h.join();
    }
}


/*
void LSH::construirBuckets() {
    for (const auto& [id, user] : *usuariosRef) {
        int firma = calcularFirma(user);
        buckets[firma].push_back(id);
    }
}
/*
int LSH::calcularFirma(const Usuario& u) {
    int nHilos = 16;
    int rango = (usuariosRef->size() + nHilos - 1) / nHilos; //rango que procesara cada hilo
    
    vector<thread> hilos;
    hilos.reserve(nHilos);
    
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
}*/
void LSH::calcularFirma() {
    unsigned int nHilos = 16;
    int rango = (usuariosRef->size() + nHilos - 1) / nHilos;

    vector<thread> hilos;
    hilos.reserve(nHilos);

    int inicio = 0, fin = 0;
    auto it = usuariosRef->begin();
    for (unsigned int t = 0; t < nHilos; ++t) {
        inicio = t * rango;
        fin = min(inicio + rango, (int)usuariosRef->size());

        hilos.emplace_back([this, inicio, fin, &it]() {
            for (int i = inicio; i < fin; ++i) {
                int firma = 0;
                for (int j = 0; j < numHashes; ++j) {
                    double suma = 0.0;
                    for (int c : it->second.cancionesEscuchadas) {
                        if (c < numCanciones)
                            suma += planos[j][c];
                    }
                    if (suma > 0)
                        firma |= (1 << j);
                }
                it->second.firma = firma;  // Guardamos la firma en el usuario
                ++it;  // Avanzamos en el mapa
            }
        });
    }

    for (auto& h : hilos) {
        h.join();
    }
}

/// -------------------------------------------------------------------------------------
int LSH::contarEnComun(const Usuario& a, const Usuario& b) {
    int comunes = 0;
    for (int c : a.cancionesEscuchadas)
        if (b.cancionesEscuchadas.count(c))
            ++comunes;
    return comunes;
}

double LSH::calcularDistanciaEuclidiana(const Usuario& usuario1, const Usuario& usuario2) {
    vector<int> v1(numCanciones, 0);
    vector<int> v2(numCanciones, 0);

    for (int c : usuario1.cancionesEscuchadas)
        if (c < numCanciones) v1[c] = 1;

    for (int c : usuario2.cancionesEscuchadas)
        if (c < numCanciones) v2[c] = 1;

    double suma = 0.0;
    for (int i = 0; i < numCanciones; ++i)
        suma += pow(v1[i] - v2[i], 2);

    return sqrt(suma);
}

void LSH::buscarSimilares(int id) {
    if (!usuariosRef->count(id)) {
        cout << "Usuario no encontrado\n";
        return;
    }

    // Obtener directamente la firma del usuario sin necesidad de recalcularla
    int firma = (*usuariosRef)[id].firma;
    auto& candidatos = buckets[firma];  // Bucket de usuarios con la misma firma

    cout << "--- Usuarios similares a " << id << " ---\n";
    for (int otro : candidatos) {
        if (otro == id) continue;  // No compararse a sí mismo
        int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro]);
        if (comunes > 0) {
            // Calcular la distancia euclidiana entre los usuarios
            double distancia = calcularDistanciaEuclidiana((*usuariosRef)[id], (*usuariosRef)[otro]);
            cout << "Usuario " << otro << " | " << comunes << " canciones comunes | Distancia: " << distancia << "\n";
        }
    }

    // Si no se encontraron similares, informamos al usuario
    if (candidatos.size() <= 1)
        cout << "No se encontraron usuarios similares\n";
}


double LSH::calcularDistanciaEntreUsuarios(int usuario1, int usuario2) {
    if (!usuariosRef->count(usuario1) || !usuariosRef->count(usuario2)) {
        throw runtime_error("Error: uno de los usuarios no existe.");
    }
    return calcularDistanciaEuclidiana((*usuariosRef)[usuario1], (*usuariosRef)[usuario2]);
}
/*
vector<int> LSH::obtenerCancionesRecomendadas(int usuarioID, int numRecomfinaciones) {
    vector<int> recomfinaciones;

    if (!usuariosRef->count(usuarioID)) {
        cout << "Usuario no encontrado\n";
        return recomfinaciones;
    }

    int firma = calcularFirmas((*usuariosRef)[usuarioID]);
    auto& candidatos = buckets[firma];
    const auto& cancionesUsuario = (*usuariosRef)[usuarioID].cancionesEscuchadas;

    unordered_map<int, int> cancionesCandidatas;
    for (int otroID : candidatos) {
        if (otroID == usuarioID) continue;
        for (int cID : (*usuariosRef)[otroID].cancionesEscuchadas) {
            if (!cancionesUsuario.count(cID)) {
                cancionesCandidatas[cID]++;
            }
        }
    }

    vector<pair<int, int>> ordenadas(cancionesCandidatas.begin(), cancionesCandidatas.end());
    sort(ordenadas.begin(), ordenadas.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < min(numRecomfinaciones, (int)ordenadas.size()); ++i)
        recomfinaciones.push_back(ordenadas[i].first);

    return recomfinaciones;
}*/

vector<int> LSH::obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones) {
    vector<int> recomendaciones;

    if (!usuariosRef->count(usuarioID)) {
        cout << "Usuario no encontrado\n";
        return recomendaciones;
    }

    // Acceder directamente a la firma precalculada del usuario
    int firma = (*usuariosRef)[usuarioID].firma;
    auto& candidatos = buckets[firma];  // Bucket de usuarios con la misma firma
    const auto& cancionesUsuario = (*usuariosRef)[usuarioID].cancionesEscuchadas;

    unordered_map<int, int> cancionesCandidatas;
    
    // Para cada candidato, buscar canciones que no haya escuchado el usuario actual
    for (int otroID : candidatos) {
        if (otroID == usuarioID) continue;  // No se compara consigo mismo
        for (int cID : (*usuariosRef)[otroID].cancionesEscuchadas) {
            if (!cancionesUsuario.count(cID)) {
                cancionesCandidatas[cID]++;  // Aumenta la "frecuencia" de la canción
            }
        }
    }

    // Ordenamos las canciones candidatas por frecuencia (más escuchadas primero)
    vector<pair<int, int>> ordenadas(cancionesCandidatas.begin(), cancionesCandidatas.end());
    sort(ordenadas.begin(), ordenadas.end(), [](auto& a, auto& b) {
        return a.second > b.second;  // Ordenamos de mayor a menor frecuencia
    });

    // Elegir las primeras 'numRecomendaciones' canciones
    for (int i = 0; i < min(numRecomendaciones, (int)ordenadas.size()); ++i) {
        recomendaciones.push_back(ordenadas[i].first);
    }

    return recomendaciones;
}


