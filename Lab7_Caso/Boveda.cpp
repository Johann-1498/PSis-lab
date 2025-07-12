#include "Boveda.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "ExcepcionEscrituraFallidaCSV.h"
#include "ExcepcionArchivoNoEncontrado.h"

Boveda::Boveda(const std::string& codigo_)
  : codigo(codigo_), activos(), registros(), rutaArchivoLog("logs/") {
    generarNombreArchivo(); // Establece la ruta completa del archivo
}

std::string Boveda::generarNombreArchivo() const {
    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d", now_tm);
    
    rutaArchivoLog = "logs/boveda_" + codigo + "_" + std::string(buffer) + ".csv";
    return rutaArchivoLog;
}

void Boveda::setRutaArchivoLog(const std::string& ruta) {
    rutaArchivoLog = ruta;
}

void Boveda::guardarEnCSV(const Registro& registro) const {
    try {
        // Verificar si el directorio existe
        std::ifstream test(rutaArchivoLog);
        if (!test.good()) {
            // Intentar crear el directorio si no existe
            system(("mkdir -p " + rutaArchivoLog.substr(0, rutaArchivoLog.find_last_of('/'))).c_str());
        }
        
        std::ofstream archivo(rutaArchivoLog, std::ios::app);
        if (!archivo.is_open()) {
            throw ExcepcionEscrituraFallidaCSV(rutaArchivoLog);
        }

        // Escribir encabezado si el archivo está vacío
        if (archivo.tellp() == 0) {
            archivo << "Fecha,Hora,TipoOperacion,CodigoBoveda,Soles,Dolares,Bonos,Joyas,MontoTotal\n";
        }

        // Convertir fecha a formato legible
        auto tiempo = std::chrono::system_clock::to_time_t(registro.fecha);
        std::tm* tiempo_tm = std::localtime(&tiempo);
        
        char fecha[11], hora[9];
        std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", tiempo_tm);
        std::strftime(hora, sizeof(hora), "%H:%M:%S", tiempo_tm);

        // Calcular montos
        double soles = registro.solicitud.count(CodigoActivo::SOLES) ? registro.solicitud.at(CodigoActivo::SOLES) : 0.0;
        double dolares = registro.solicitud.count(CodigoActivo::DOLARES) ? registro.solicitud.at(CodigoActivo::DOLARES) : 0.0;
        double bonos = registro.solicitud.count(CodigoActivo::BONO) ? registro.solicitud.at(CodigoActivo::BONO) : 0.0;
        double joyas = registro.solicitud.count(CodigoActivo::JOYA) ? registro.solicitud.at(CodigoActivo::JOYA) : 0.0;
        double montoTotal = soles + dolares + bonos + joyas;

        // Escribir registro
        archivo << fecha << ","
                << hora << ","
                << static_cast<int>(registro.tipo) << ","
                << codigo << ","
                << soles << ","
                << dolares << ","
                << bonos << ","
                << joyas << ","
                << montoTotal << "\n";

        archivo.close();
    } catch (const std::exception& e) {
        throw ExcepcionEscrituraFallidaCSV(rutaArchivoLog);
    }
}

SolicitudActivos Boveda::crearSolicitud() const {
    SolicitudActivos sol;
    double monto;

    std::cout << "Cantidad en Soles: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::SOLES] = monto;

    std::cout << "Cantidad en Dolares: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::DOLARES] = monto;

    std::cout << "Cantidad en Bonos: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::BONO] = monto;

    std::cout << "Cantidad en Joyas: ";
    std::cin >> monto;
    if (monto > 0) sol[CodigoActivo::JOYA] = monto;

    return sol;
}

void Boveda::registrarRegistro(TipoOperacion tipo, const SolicitudActivos& sol) {
    registros.emplace_back(tipo, sol);
    try {
        guardarEnCSV(registros.back());
    } catch (const ExcepcionEscrituraFallidaCSV& e) {
        // Reintentar una vez
        try {
            guardarEnCSV(registros.back());
        } catch (...) {
            // Si falla de nuevo, lanzar excepción
            throw;
        }
    }
}

void Boveda::depositar(const SolicitudActivos& sol) {
    activos.depositar(sol);
    registrarRegistro(TipoOperacion::DEPOSITO, sol);
}

void Boveda::retirar(const SolicitudActivos& sol) {
    activos.retirar(sol);
    registrarRegistro(TipoOperacion::RETIRO, sol);
}

void Boveda::transportar(Boveda& destino, const SolicitudActivos& sol) {
    activos.retirar(sol);
    destino.activos.depositar(sol);
    
    // Registrar en ambas bóvedas
    registrarRegistro(TipoOperacion::TRASLADO, sol);
    destino.registrarRegistro(TipoOperacion::TRASLADO, sol);
}

const std::vector<Registro>& Boveda::getRegistros() const {
    return registros;
}