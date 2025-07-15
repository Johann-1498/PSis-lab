// --- Archivo: LSH.h (MODIFICADO) ---
#pragma once
#include <unordered_map>
#include <vector>
#include "Usuario.h"

class LSH {
private:
    int numHashes;
    int numCanciones; // Todavía lo necesitamos para la validación
    // ELIMINADO: La matriz 'planos' que consumía toda la memoria
    // std::vector<std::vector<double>> planos; 
    std::unordered_map<int, std::vector<int>> buckets;
    std::unordered_map<int, Usuario>* usuariosRef;

    // ELIMINADO: Ya no necesitamos generar una matriz gigante
    // void generarPlanos(); 
    void calcularFirmas(); // Esta función ahora hará todo el trabajo
    void construirBuckets();
    int contarEnComun(const Usuario& a, const Usuario& b);
    double calcularDistanciaEuclidiana(const Usuario& u1, const Usuario& u2);

public:
    LSH(int hashes, int totalCanciones, std::unordered_map<int, Usuario>& usuarios);
    void buscarSimilares(int id);
    double calcularDistanciaEntreUsuarios(int u1_id, int u2_id);
    std::vector<int> obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones = 10);
};