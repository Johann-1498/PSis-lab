#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "usuario.h"
#include "cancion.h"

class Reader {
public:
    static void leerCSV(const std::string& rutaCSV,
                                std::unordered_map<int, Usuario>& usuarios,
                                std::unordered_map<int, Cancion>& canciones) {
        std::ifstream archivo(rutaCSV);
        if (!archivo.is_open()) {
            std::cerr << "Error, no se puede acceder al archivo " << rutaCSV << std::endl;
            return;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string campo;
            int usuarioID, cancionID;
            double calificacion;

            std::getline(ss, campo, ',');
            usuarioID = std::stoi(campo);
            std::getline(ss, campo, ',');
            cancionID = std::stoi(campo);
            std::getline(ss, campo, ',');
            calificacion = std::stod(campo);

            usuarios[usuarioID].id = usuarioID;
            usuarios[usuarioID].cancionesEscuchadas.insert(cancionID);

            canciones[cancionID].id = cancionID;
            canciones[cancionID].cantidadEscuchas++;
            canciones[cancionID].sumaCalificaciones += calificacion;
        }

        archivo.close();
    }
};
