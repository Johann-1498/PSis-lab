// --- Archivo: Reader.cpp ---
/*#include "Reader.h"
#include "Registro.h"
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>
#include <unistd.h> // Para write() y close()
#include <cstdio>   // Para perror()
/*
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
}*/

// --- Reader.cpp ---
#include "Reader.h"
#include "Registro.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>
#include <unistd.h>    // write(), close()
#include <cstdio>      // perror()



void Reader::procesarRango(
    const std::vector<std::string>& lineas,
    int start,
    int end,
    int pipeWriteFd,
    std::mutex& pipeMutex
) {
    // Parsear todas las líneas asignadas y acumular registros
    std::vector<Registro> registros;
    registros.reserve(end - start);

    for (int i = start; i < end; ++i) {
        const auto& texto = lineas[i];
        std::stringstream ss(texto);
        Registro reg;
        std::string campo;

        if (!std::getline(ss, campo, ',') || campo.empty()) continue;
        reg.usuarioID = std::stoi(campo);
        if (!std::getline(ss, campo, ',') || campo.empty()) continue;
        reg.cancionID = std::stoi(campo);
        if (!std::getline(ss, campo, ',') || campo.empty()) continue;
        reg.calif = std::stod(campo);

        registros.push_back(reg);
    }

    // Escribir todos los registros de una sola vez
    std::lock_guard<std::mutex> lock(pipeMutex);
    if (!registros.empty()) {
        ssize_t bytes = registros.size() * sizeof(Registro);
        ssize_t escritos = write(pipeWriteFd, registros.data(), bytes);
        if (escritos != bytes) {
            perror("Error al escribir en pipe");
        }
    }
}

void Reader::leerCSVConHilos(const std::string& rutaCSV, int pipeWriteFd, int numHilos) {
    std::ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        perror(("Error al abrir CSV: " + rutaCSV).c_str());
        exit(EXIT_FAILURE);
    }

    // Carga todas las líneas en memoria una sola vez
    std::vector<std::string> lineas;
    lineas.reserve(1000000);
    std::string linea;
    while (std::getline(archivo, linea)) {
        lineas.push_back(std::move(linea));
    }
    archivo.close();

    // Calcula rangos para cada hilo
    int total = (int)lineas.size();
    int rango = (total + numHilos - 1) / numHilos;

    std::mutex pipeMutex;
    std::vector<std::thread> hilos;
    hilos.reserve(numHilos);

    for (int t = 0; t < numHilos; ++t) {
        int inicio = t * rango;
        int fin = std::min(inicio + rango, total);
        if (inicio >= fin) break;
        hilos.emplace_back(procesarRango,
                           std::cref(lineas),
                           inicio, fin,
                           pipeWriteFd,
                           std::ref(pipeMutex));
    }

    // Espera a que terminen los hilos
    for (auto& t : hilos) {
        if (t.joinable()) t.join();
    }

    // Cierra el pipe para señal al padre
    close(pipeWriteFd);
}