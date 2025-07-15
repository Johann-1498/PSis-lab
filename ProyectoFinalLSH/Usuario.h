#pragma once
#include <unordered_set>

struct Usuario {
    int id;
    std::unordered_set<int> cancionesEscuchadas;  // IDs de canciones
    int firma;
};
