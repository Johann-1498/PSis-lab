// Archivo: main.cpp
#include "ranking_canciones.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>

struct Usuario {
    int id;
    std::unordered_set<int> cancionesEscuchadas;
};

void leerArchivo(const std::string& nombreArchivo,
                 std::unordered_map<int, Usuario>& usuarios,
                 std::unordered_map<int, Cancion>& canciones) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campo;

        getline(ss, campo, ',');
        int usuarioID = std::stoi(campo);

        getline(ss, campo, ',');
        int cancionID = std::stoi(campo);

        getline(ss, campo, ',');
        double calificacion = std::stod(campo);

        // Crear o actualizar usuario
        usuarios[usuarioID].id = usuarioID;
        usuarios[usuarioID].cancionesEscuchadas.insert(cancionID);

        // Crear o actualizar cancion
        canciones[cancionID].id = cancionID;
        canciones[cancionID].cantidadEscuchas++;
        canciones[cancionID].sumaCalificaciones += calificacion;
    }
    archivo.close();
}

int main() {
    std::unordered_map<int, Usuario> usuarios;
    std::unordered_map<int, Cancion> canciones;

    std::string nombreArchivo = "large.csv";
    leerArchivo(nombreArchivo, usuarios, canciones);

    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);

    std::cout << "\nTop 5 canciones mejor calificadas:\n";
    ranking.mostrarTop(5);

    return 0;
}
