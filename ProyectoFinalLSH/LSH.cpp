#include "LSH.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <random>


using namespace std;

LSH::LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios)
    : numHashes(hashes), numCanciones(totalCanciones), usuariosRef(&usuarios) {
    generarPlanos();
    construirBuckets();
}

void LSH::generarPlanos() {
    mt19937 gen(random_device{}());
    normal_distribution<double> dist(0.0, 1.0);
    planos.resize(numHashes, vector<double>(numCanciones));
    for (int i = 0; i < numHashes; ++i)
        for (int j = 0; j < numCanciones; ++j)
            planos[i][j] = dist(gen);
}

void LSH::construirBuckets() {
    for (const auto& [id, user] : *usuariosRef) {
        int firma = calcularFirma(user);
        buckets[firma].push_back(id);
    }
}

int LSH::calcularFirma(const Usuario& u) {
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

    int firma = calcularFirma((*usuariosRef)[id]);
    auto& candidatos = buckets[firma];

    cout << "--- Usuarios similares a " << id << " ---\n";
    for (int otro : candidatos) {
        if (otro == id) continue;
        int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro]);
        if (comunes > 0) {
            double distancia = calcularDistanciaEuclidiana((*usuariosRef)[id], (*usuariosRef)[otro]);
            cout << "Usuario " << otro << " | " << comunes << " canciones comunes | Distancia: " << distancia << "\n";
        }
    }

    if (candidatos.size() <= 1)
        cout << "No se encontraron usuarios similares\n";
}

double LSH::calcularDistanciaEntreUsuarios(int usuario1, int usuario2) {
    if (!usuariosRef->count(usuario1) || !usuariosRef->count(usuario2)) {
        throw runtime_error("Error: uno de los usuarios no existe.");
    }
    return calcularDistanciaEuclidiana((*usuariosRef)[usuario1], (*usuariosRef)[usuario2]);
}

vector<int> LSH::obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones) {
    vector<int> recomendaciones;

    if (!usuariosRef->count(usuarioID)) {
        cout << "Usuario no encontrado\n";
        return recomendaciones;
    }

    int firma = calcularFirma((*usuariosRef)[usuarioID]);
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

    for (int i = 0; i < min(numRecomendaciones, (int)ordenadas.size()); ++i)
        recomendaciones.push_back(ordenadas[i].first);

    return recomendaciones;
}

