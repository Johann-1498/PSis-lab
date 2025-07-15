/*#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "usuario.h"
#include "cancion.h"
/*
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
*/
#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>     // write(), close()
#include <cstdio>       // perror()
#include "Usuario.h"
#include "Cancion.h"
#include "Registro.h"

class Reader {
public:
    // Versión original: carga directamente en los mapas
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

    // Nueva sobrecarga: lee CSV y envía cada registro por pipe al padre
    static void leerCSV(const std::string& rutaCSV, int pipeWriteFd) {
        std::ifstream archivo(rutaCSV);
        if (!archivo.is_open()) {
            perror(("Error al abrir CSV: " + rutaCSV).c_str());
            exit(EXIT_FAILURE);
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            Registro reg;
            std::string campo;

            // usuarioID
            if (!std::getline(ss, campo, ',')) continue;
            reg.usuarioID = std::stoi(campo);
            // cancionID
            if (!std::getline(ss, campo, ',')) continue;
            reg.cancionID = std::stoi(campo);
            // calificación
            if (!std::getline(ss, campo, ',')) continue;
            reg.calif = std::stod(campo);

            // escribir struct al pipe
            ssize_t escrito = write(pipeWriteFd, &reg, sizeof(reg));
            if (escrito != sizeof(reg)) {
                perror("Error al escribir en pipe");
                break;
            }
        }

        archivo.close();
        close(pipeWriteFd);  // señal de EOF
    }
};
