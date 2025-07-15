// --- Archivo: Reader.cpp ---
#include "Reader.h"
#include "Registro.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>
#include <unistd.h> // Para write() y close()
#include <cstdio>   // Para perror()

void Reader::leerCSVConHilos(const std::string& rutaCSV, int pipeWriteFd, int numHilos) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        perror(("Error al abrir CSV: " + rutaCSV).c_str());
        exit(EXIT_FAILURE);
    }

    std::mutex pipeMutex;
    std::vector<std::thread> hilos;
    std::vector<std::string> bufferDeLineas;
    const size_t TAMANO_LOTE = 50000; // Número de líneas por lote a procesar por los hilos

    std::string linea;
    while (std::getline(archivo, linea)) {
        bufferDeLineas.push_back(linea);
        if (bufferDeLineas.size() >= TAMANO_LOTE) {
            // Cuando el buffer está lleno, crea un hilo para procesarlo
            hilos.emplace_back(procesarLoteDeLineas, bufferDeLineas, pipeWriteFd, std::ref(pipeMutex));
            bufferDeLineas.clear(); // Limpia el buffer para el siguiente lote
        }
    }

    // Procesa cualquier línea restante en el buffer
    if (!bufferDeLineas.empty()) {
        hilos.emplace_back(procesarLoteDeLineas, bufferDeLineas, pipeWriteFd, std::ref(pipeMutex));
    }

    // Espera a que todos los hilos terminen su trabajo
    for (auto& t : hilos) {
        if (t.joinable()) {
            t.join();
        }
    }

    archivo.close();
    close(pipeWriteFd); // Cierra el pipe para señalar al padre que no se escribirán más datos
}

void Reader::procesarLoteDeLineas(const std::vector<std::string>& lote, int pipeWriteFd, std::mutex& pipeMutex) {
    std::vector<Registro> registrosLocales;
    registrosLocales.reserve(lote.size());

    for (const auto& linea : lote) {
        std::stringstream ss(linea);
        Registro reg;
        std::string campo;

        // Parsea la línea CSV
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            reg.usuarioID = std::stoi(campo);
        } else continue;

        if (std::getline(ss, campo, ',') && !campo.empty()) {
            reg.cancionID = std::stoi(campo);
        } else continue;
        
        if (std::getline(ss, campo, ',') && !campo.empty()) {
            reg.calif = std::stod(campo);
        } else continue;

        registrosLocales.push_back(reg);
    }

    // Bloquea el mutex para escribir en el pipe de forma segura
    std::lock_guard<std::mutex> lock(pipeMutex);
    for (const auto& reg : registrosLocales) {
        ssize_t escrito = write(pipeWriteFd, &reg, sizeof(reg));
        if (escrito != sizeof(reg)) {
            perror("Error al escribir en pipe");
            break; // Si hay un error, detiene la escritura
        }
    }
}