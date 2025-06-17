#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "usuario.h"

class LSH {
private:
    int numHashes;
    int numCanciones;
    std::vector<std::vector<double>> planos;
    std::unordered_map<int, std::vector<int>> buckets;
    std::unordered_map<int, Usuario>* usuariosRef;

    void generarPlanos();
    void construirBuckets();
    int calcularFirma(const Usuario& u);
    int contarEnComun(const Usuario& a, const Usuario& b);

public:
    LSH(int hashes, int totalCanciones, std::unordered_map<int, Usuario>& usuarios);
    void buscarSimilares(int id);
};
