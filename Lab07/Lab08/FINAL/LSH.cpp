#include "lsh.h"
#include <random>
#include <cmath>
#include <iostream>

LSH::LSH(int hashes, int totalCanciones, std::unordered_map<int, Usuario>& usuarios)
    : numHashes(hashes), numCanciones(totalCanciones), usuariosRef(&usuarios) {
    generarPlanos();
    construirBuckets();
}

void LSH::generarPlanos() {
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> dist(0.0, 1.0);
    planos.resize(numHashes, std::vector<double>(numCanciones));
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

void LSH::buscarSimilares(int id) {
    if (!usuariosRef->count(id)) {
        std::cout << "Usuario no encontrado.\n";
        return;
    }

    int firma = calcularFirma((*usuariosRef)[id]);
    auto& candidatos = buckets[firma];

    std::cout << "\n👥 Usuarios similares a " << id << ":\n";
    for (int otro : candidatos) {
        if (otro == id) continue;
        int comunes = contarEnComun((*usuariosRef)[id], (*usuariosRef)[otro]);
        if (comunes > 0)
            std::cout << "- Usuario " << otro << " con " << comunes << " canciones en común\n";
    }

    if (candidatos.size() <= 1)
        std::cout << "(No se encontraron usuarios similares)\n";
}
