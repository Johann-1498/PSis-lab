#ifndef SISTEMA_METRICAS_H
#define SISTEMA_METRICAS_H

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <psapi.h>
#include <chrono>

// clase para medir rendimiento del sistema - tiempo y memoria
class SistemaMetricas {
private:
    std::chrono::high_resolution_clock::time_point inicioTiempo;
    SIZE_T memoriaInicial;
    
public:
    // inicia el contador de tiempo y memoria
    void iniciarMedicion() {
        inicioTiempo = std::chrono::high_resolution_clock::now();
        
        // obtener memoria inicial usando win32 api
        PROCESS_MEMORY_COUNTERS pmc;
        HANDLE proceso = GetCurrentProcess();
        if (GetProcessMemoryInfo(proceso, &pmc, sizeof(pmc))) {
            memoriaInicial = pmc.WorkingSetSize;
        } else {
            memoriaInicial = 0;
        }
    }
    
    // muestra el tiempo transcurrido y memoria usada
    void mostrarMetricas() {
        // calcular tiempo transcurrido
        auto finTiempo = std::chrono::high_resolution_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(finTiempo - inicioTiempo);
        
        // obtener memoria actual
        PROCESS_MEMORY_COUNTERS pmc;
        HANDLE proceso = GetCurrentProcess();
        SIZE_T memoriaActual = 0;
        if (GetProcessMemoryInfo(proceso, &pmc, sizeof(pmc))) {
            memoriaActual = pmc.WorkingSetSize;
        }
        
        // mostrar resultados
        std::cout << "\n=== METRICAS DEL SISTEMA ===\n";
        std::cout << "Tiempo de ejecucion: " << duracion.count() << " ms\n";
        std::cout << "Memoria inicial: " << std::fixed << std::setprecision(2) 
                  << (memoriaInicial / 1024.0 / 1024.0) << " MB\n";
        std::cout << "Memoria actual: " << std::fixed << std::setprecision(2) 
                  << (memoriaActual / 1024.0 / 1024.0) << " MB\n";
        std::cout << "Memoria usada: " << std::fixed << std::setprecision(2) 
                  << ((memoriaActual - memoriaInicial) / 1024.0 / 1024.0) << " MB\n";
        std::cout << "=============================\n";
    }
    
    // obtiene solo el tiempo transcurrido en ms
    long long obtenerTiempo() {
        auto finTiempo = std::chrono::high_resolution_clock::now();
        auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(finTiempo - inicioTiempo);
        return duracion.count();
    }
    
    // obtiene solo la memoria usada en MB
    double obtenerMemoriaUsada() {
        PROCESS_MEMORY_COUNTERS pmc;
        HANDLE proceso = GetCurrentProcess();
        SIZE_T memoriaActual = 0;
        if (GetProcessMemoryInfo(proceso, &pmc, sizeof(pmc))) {
            memoriaActual = pmc.WorkingSetSize;
        }
        return (memoriaActual - memoriaInicial) / 1024.0 / 1024.0;
    }
};

#endif