// --- Archivo: Reader.h ---
#pragma once

#include <string>
#include <vector>
#include <mutex>

class Reader {
public:
    // Lee el CSV usando múltiples hilos y escribe en un pipe
    static void leerCSVConHilos(const std::string& rutaCSV, int pipeWriteFd, int numHilos = 16);

private:
    // Función que será ejecutada por cada hilo para procesar un lote de líneas
    //static void procesarLoteDeLineas(const std::vector<std::string>& lote, int pipeWriteFd, std::mutex& pipeMutex);
    static void procesarRango(
        const std::vector<std::string>& lineas,
        int start,
        int end,
        int pipeWriteFd,
        std::mutex& pipeMutex
    );
};