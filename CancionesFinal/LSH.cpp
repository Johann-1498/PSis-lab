/*// --- Archivo: LSH.cpp (MODIFICADO) ---
#include "LSH.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

// El constructor ahora es mucho más simple
LSH::LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios)
    : numHashes(hashes), numCanciones(totalCanciones), usuariosRef(&usuarios) {
    // Ya no llamamos a generarPlanos()
    calcularFirmas();
    construirBuckets();
}

// Se elimina la función generarPlanos() por completo.

void LSH::calcularFirmas() {
    unsigned int nHilos = thread::hardware_concurrency();
    vector<thread> hilos;
    
    // Convertimos el mapa a un vector para un acceso seguro por índice en los hilos
    vector<pair<const int, Usuario>*> usuariosVec;
    usuariosVec.reserve(usuariosRef->size());
    for(auto it = usuariosRef->begin(); it != usuariosRef->end(); ++it) {
        usuariosVec.push_back(&(*it));
    }

    int rango = (usuariosVec.size() + nHilos - 1) / nHilos;

    for (unsigned int t = 0; t < nHilos; ++t) {
        int inicio = t * rango;
        int fin = min(inicio + rango, (int)usuariosVec.size());
        if(inicio >= fin) continue;

        hilos.emplace_back([this, inicio, fin, &usuariosVec]() {
            // Cada hilo tiene su propio generador de números aleatorios
            normal_distribution<double> dist(0.0, 1.0);

            for (int i = inicio; i < fin; ++i) {
                Usuario& user = usuariosVec[i]->second;
                int firma = 0;
                for (int j = 0; j < numHashes; ++j) {
                    double suma = 0.0;
                    
                    // --- LA MAGIA ESTÁ AQUÍ ---
                    // Creamos un generador para este hash (j). Usar 'j' como seed
                    // garantiza que para el mismo hash, se generará la misma
                    // secuencia de números aleatorios en todas las llamadas.
                    mt19937 gen(j); 

                    for (int c : user.cancionesEscuchadas) {
                        if (c < numCanciones) {
                            // En lugar de buscar en una matriz, generamos el número al vuelo.
                            // Para que sea determinista para la canción 'c',
                            // descartamos 'c' números aleatorios.
                            gen.discard(c);
                            suma += dist(gen);
                            
                            // Reseteamos el generador para la siguiente canción,
                            // pero con el mismo seed 'j'
                            gen.seed(j); 
                        }
                    }
                    if (suma > 0) firma |= (1 << j);
                }
                user.firma = firma;
            }
        });
    }
    for (auto& h : hilos) h.join();
}


// El resto de las funciones de LSH.cpp no necesitan cambios.
// (Las pego abajo para que tengas el archivo completo)

void LSH::construirBuckets() {
    for (auto const& [id, user] : *usuariosRef) {
        buckets[user.firma].push_back(id);
    }
}

int LSH::contarEnComun(const Usuario& a, const Usuario& b) {
    int comunes = 0;
    const auto& set_pequeno = (a.cancionesEscuchadas.size() < b.cancionesEscuchadas.size()) ? a.cancionesEscuchadas : b.cancionesEscuchadas;
    const auto& set_grande = (a.cancionesEscuchadas.size() >= b.cancionesEscuchadas.size()) ? a.cancionesEscuchadas : b.cancionesEscuchadas;
    for (int c : set_pequeno) {
        if (set_grande.count(c)) ++comunes;
    }
    return comunes;
}

double LSH::calcularDistanciaEuclidiana(const Usuario& u1, const Usuario& u2) {
    double suma = 0.0;
    unordered_set<int> todas_canciones = u1.cancionesEscuchadas;
    todas_canciones.insert(u2.cancionesEscuchadas.begin(), u2.cancionesEscuchadas.end());

    for (int c : todas_canciones) {
        if (c < numCanciones) {
            bool enU1 = u1.cancionesEscuchadas.count(c);
            bool enU2 = u2.cancionesEscuchadas.count(c);
            suma += pow((enU1 ? 1 : 0) - (enU2 ? 1 : 0), 2);
        }
    }
    return sqrt(suma);
}

void LSH::buscarSimilares(int id) {
    if (!usuariosRef->count(id)) {
        cout << "Usuario no encontrado\n";
        return;
    }
    int firma = (*usuariosRef)[id].firma;
    const auto& candidatos = buckets[firma];

    cout << "--- Usuarios similares a " << id << " (misma firma LSH) ---\n";
    int similaresEncontrados = 0;
    for (int otro_id : candidatos) {
        if (otro_id == id) continue;
        int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro_id]);
        if (comunes > 0) {
            double dist = calcularDistanciaEuclidiana((*usuariosRef)[id], (*usuariosRef)[otro_id]);
            cout << "Usuario " << otro_id << " | " << comunes << " canciones en comun | Distancia: " << dist << "\n";
            similaresEncontrados++;
        }
    }
    if (similaresEncontrados == 0) cout << "No se encontraron usuarios similares en el mismo bucket.\n";
}

double LSH::calcularDistanciaEntreUsuarios(int u1_id, int u2_id) {
    if (!usuariosRef->count(u1_id) || !usuariosRef->count(u2_id)) {
        throw runtime_error("Error: uno o ambos usuarios no existen.");
    }
    return calcularDistanciaEuclidiana((*usuariosRef)[u1_id], (*usuariosRef)[u2_id]);
}

vector<int> LSH::obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones) {
    if (!usuariosRef->count(usuarioID)) {
        cout << "Usuario no encontrado\n";
        return {};
    }

    int firma = (*usuariosRef)[usuarioID].firma;
    const auto& candidatos = buckets[firma];
    const auto& cancionesUsuario = (*usuariosRef)[usuarioID].cancionesEscuchadas;

    unordered_map<int, int> conteoCanciones;
    for (int otroID : candidatos) {
        if (otroID == usuarioID) continue;
        for (int cancionID : (*usuariosRef)[otroID].cancionesEscuchadas) {
            if (cancionesUsuario.find(cancionID) == cancionesUsuario.end()) {
                conteoCanciones[cancionID]++;
            }
        }
    }

    vector<pair<int, int>> ordenadas(conteoCanciones.begin(), conteoCanciones.end());
    sort(ordenadas.begin(), ordenadas.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    vector<int> recomendaciones;
    for (int i = 0; i < min((int)ordenadas.size(), numRecomendaciones); ++i) {
        recomendaciones.push_back(ordenadas[i].first);
    }
    return recomendaciones;
}*/

// --- LSH.cpp (actualizado) ---
// --- LSH.cpp ---
#include "LSH.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

LSH::LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios)
    : numHashes(hashes),
      numCanciones(totalCanciones),
      usuariosRef(&usuarios),
      weights(hashes, vector<double>(totalCanciones))  // <-- inicializa weights
{
    // 1) Precalcular la matriz de pesos
    {
        mt19937 gen(42);
        normal_distribution<double> dist(0.0, 1.0);
        for (int j = 0; j < numHashes; ++j) {
            for (int c = 0; c < numCanciones; ++c) {
                weights[j][c] = dist(gen);
            }
        }
    }

    // 2) Construir firmas y buckets
    calcularFirmas();
    construirBuckets();
}

void LSH::calcularFirmas() {
    unsigned int nHilos = thread::hardware_concurrency();
    vector<thread> hilos;

    // convertir mapa a vector de punteros para indexar
    vector<pair<const int, Usuario>*> usuariosVec;
    usuariosVec.reserve(usuariosRef->size());
    for (auto& par : *usuariosRef) {
        usuariosVec.push_back(&par);
    }

    int rango = (usuariosVec.size() + nHilos - 1) / nHilos;

    for (unsigned int t = 0; t < nHilos; ++t) {
        int inicio = t * rango;
        int fin    = min(inicio + rango, (int)usuariosVec.size());
        if (inicio >= fin) continue;

        hilos.emplace_back([this, inicio, fin, &usuariosVec]() {
            for (int i = inicio; i < fin; ++i) {
                Usuario& user = usuariosVec[i]->second;
                int firma = 0;

                // usar weights en lugar de discard()/seed()
                for (int j = 0; j < numHashes; ++j) {
                    double suma = 0.0;
                    for (int c : user.cancionesEscuchadas) {
                        if (c < numCanciones) {
                            suma += weights[j][c];
                        }
                    }
                    if (suma > 0.0) {
                        firma |= (1 << j);
                    }
                }
                user.firma = firma;
            }
        });
    }

    for (auto& h : hilos) h.join();
}

void LSH::construirBuckets() {
    for (auto const& [id, user] : *usuariosRef) {
        buckets[user.firma].push_back(id);
    }
}

int LSH::contarEnComun(const Usuario& a, const Usuario& b) {
    int comunes = 0;
    const auto& menor = (a.cancionesEscuchadas.size() < b.cancionesEscuchadas.size())
                        ? a.cancionesEscuchadas : b.cancionesEscuchadas;
    const auto& mayor = (a.cancionesEscuchadas.size() >= b.cancionesEscuchadas.size())
                        ? a.cancionesEscuchadas : b.cancionesEscuchadas;
    for (int c : menor) {
        if (mayor.count(c)) ++comunes;
    }
    return comunes;
}

double LSH::calcularDistanciaEuclidiana(const Usuario& u1, const Usuario& u2) {
    double suma = 0.0;
    unordered_set<int> todas = u1.cancionesEscuchadas;
    todas.insert(u2.cancionesEscuchadas.begin(), u2.cancionesEscuchadas.end());
    for (int c : todas) {
        if (c < numCanciones) {
            bool en1 = u1.cancionesEscuchadas.count(c);
            bool en2 = u2.cancionesEscuchadas.count(c);
            suma += pow((en1 ? 1 : 0) - (en2 ? 1 : 0), 2);
        }
    }
    return sqrt(suma);
}
/*
void LSH::buscarSimilares(int id) {
    if (!usuariosRef->count(id)) {
        cout << "Usuario no encontrado\n";
        return;
    }
    int firma = (*usuariosRef)[id].firma;
    const auto& candidatos = buckets[firma];

    cout << "--- Usuarios similares a " << id << " ---\n";
    int encontrados = 0;
    for (int otro : candidatos) {
        if (otro == id) continue;
        int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro]);
        if (comunes > 0) {
            double dist = calcularDistanciaEuclidiana((*usuariosRef)[id], (*usuariosRef)[otro]);
            cout << "Usuario " << otro
                 << " | comunes: " << comunes
                 << " | distancia: " << dist << "\n";
            ++encontrados;
        }
    }
    if (encontrados == 0)
        cout << "No hay usuarios similares en el mismo bucket.\n";
}*/
void LSH::buscarSimilares(int id) {
    if (!usuariosRef->count(id)) {
        cout << "Usuario no encontrado\n";
        return;
    }
    const Usuario& base = (*usuariosRef)[id];
    int firma = base.firma;
    const auto& candidatos = buckets[firma];

    // 1) Recolectar candidatos con distancia
    struct Info { int otro, comunes; double dist; };
    vector<Info> similars;
    similars.reserve(candidatos.size());

    for (int otro_id : candidatos) {
        if (otro_id == id) continue;
        const Usuario& u2 = (*usuariosRef)[otro_id];
        int comunes = contarEnComun(base, u2);
        if (comunes > 0) {
            double dist = calcularDistanciaEuclidiana(base, u2);
            similars.push_back({otro_id, comunes, dist});
        }
    }

    if (similars.empty()) {
        cout << "No se encontraron usuarios similares en el mismo bucket.\n";
        return;
    }

    // 2) Ordenar por distancia ascendente
    sort(similars.begin(), similars.end(),
         [](auto& a, auto& b){ return a.dist < b.dist; });

    // 3) Imprimir
    cout << "--- Usuarios similares a " << id << " (ordenados por distancia) ---\n";
    for (auto& info : similars) {
        cout << "Usuario " << info.otro
             << " | comunes: " << info.comunes
             << " | distancia: " << info.dist << "\n";
    }
}

double LSH::calcularDistanciaEntreUsuarios(int u1_id, int u2_id) {
    if (!usuariosRef->count(u1_id) || !usuariosRef->count(u2_id)) {
        throw runtime_error("Error: usuario(s) no existen.");
    }
    return calcularDistanciaEuclidiana((*usuariosRef)[u1_id], (*usuariosRef)[u2_id]);
}

vector<int> LSH::obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones) {
    if (!usuariosRef->count(usuarioID)) {
        cout << "Usuario no encontrado\n";
        return {};
    }
    int firma = (*usuariosRef)[usuarioID].firma;
    const auto& candidatos = buckets[firma];
    const auto& escuchadas = (*usuariosRef)[usuarioID].cancionesEscuchadas;

    unordered_map<int,int> conteo;
    for (int otro : candidatos) {
        if (otro == usuarioID) continue;
        for (int c : (*usuariosRef)[otro].cancionesEscuchadas) {
            if (!escuchadas.count(c))
                ++conteo[c];
        }
    }

    vector<pair<int,int>> vec(conteo.begin(), conteo.end());
    sort(vec.begin(), vec.end(), [](auto& a, auto& b){ return a.second > b.second; });

    vector<int> res;
    for (int i = 0; i < min((int)vec.size(), numRecomendaciones); ++i)
        res.push_back(vec[i].first);
    return res;
}
