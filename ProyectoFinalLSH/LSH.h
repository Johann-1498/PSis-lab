#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Usuario.h"
#include "iostream"
using namespace std;

class LSH {
private:
    int numHashes;                      
    int numCanciones;                  
    vector<vector<double>> planos;     // Vectores aleatorios para firmas hash
    unordered_map<int, vector<int>> buckets; 
    unordered_map<int, Usuario>* usuariosRef;

    void generarPlanos(); 
    void construirBuckets(); // Asocia usuarios a buckets por su firma hash
    void calcularFirma(); // Calcula la firma de un usuario
    int contarEnComun(const Usuario& a, const Usuario& b); // Canciones en común
    double calcularDistanciaEuclidiana(const Usuario& usuario1, const Usuario& usuario2); // Similitud

public:
    LSH(int hashes, int totalCanciones, unordered_map<int, Usuario>& usuarios);

    void buscarSimilares(int id); // Imprime usuarios similares por bucket
    double calcularDistanciaEntreUsuarios(int usuario1, int usuario2); // Distancia entre dos usuarios
    vector<int> obtenerCancionesRecomendadas(int usuarioID, int numRecomendaciones = 10); // Recomendaciones
};
