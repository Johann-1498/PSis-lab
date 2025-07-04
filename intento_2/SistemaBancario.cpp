#include "SistemaBancario.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>      // Asegúrate de que este include esté presente
#include "Plaza.h"
#include "Boveda.h"
#include "excepciones/OperacionException.h"

// --- Funciones de Utilidad ---
std::string tipoParadaToString(TipoParada tipo) {
    return tipo == TipoParada::RECOGER ? "RECOGER" : "ENTREGAR";
}

std::string codigoActivoToString(CodigoActivo cod) {
    switch(cod) {
        case CodigoActivo::SOLES: return "Soles";
        case CodigoActivo::DOLARES: return "Dólares";
        case CodigoActivo::BONO: return "Bono";
        case CodigoActivo::JOYA: return "Joya";
    }
    return "DESCONOCIDO";
}
// --- Fin Funciones de Utilidad ---

// :: Constructor ::
SistemaBancario::SistemaBancario() 
    : banco("BCP"), transportador("Hermes") {
    std::cout << "Inicializando Sistema Bancario...\n";
    poblarDatosIniciales();
}

// :: Métodos Públicos ::
void SistemaBancario::run() {
    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        std::cin >> opcion;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1: ejecutarReporteDiario(); break;
            case 2: ejecutarReporteMensual(); break;
            case 3: ejecutarOperacionCSV(); break;
            case 4: mostrarEstadoGeneral(); break;
            case 0: std::cout << "Saliendo del sistema...\n"; break;
            default: std::cout << "Opción no válida. Intente de nuevo.\n"; break;
        }
    }
}

// :: Métodos Privados ::
void SistemaBancario::poblarDatosIniciales() {
    // Esta es una solución temporal. Plaza debería ser gestionada de otra forma.
    static Plaza lima{"Lima", "Av. Javier Prado", "LIM01"};
    static Plaza arequipa{"Arequipa", "Calle Mercaderes", "AQP01"};
    static Plaza cusco{"Cusco", "Av. del Sol", "CUS01"};
    static Plaza trujillo{"Trujillo", "Av. España", "TRU01"};
    static Plaza piura{"Piura", "Calle Lima", "PIU01"};
    
    banco.agregarBoveda("BCP_LIMA", &lima);
    banco.agregarBoveda("BCP_AREQUIPA", &arequipa);
    banco.agregarBoveda("BCP_CUSCO", &cusco);
    banco.agregarBoveda("BCP_TRUJILLO", &trujillo);
    banco.agregarBoveda("BCP_PIURA", &piura);

    try {
        Boveda* b_lima = banco.getBoveda("BCP_LIMA");
        b_lima->depositar(CodigoActivo::SOLES, 50000);
        b_lima->depositar(CodigoActivo::DOLARES, 20000);
        
        // *** CORRECCIÓN AQUÍ ***
        // Depositar varios bonos con valores específicos
        b_lima->depositar(CodigoActivo::BONO, 500); // El bono que el CSV va a pedir
        b_lima->depositar(CodigoActivo::BONO, 1000);
        b_lima->depositar(CodigoActivo::BONO, 250);

        Boveda* b_aqp = banco.getBoveda("BCP_AREQUIPA");
        b_aqp->depositar(CodigoActivo::SOLES, 10000);

        Boveda* b_cusco = banco.getBoveda("BCP_CUSCO");
        b_cusco->depositar(CodigoActivo::DOLARES, 15000);
        Boveda* b_trujillo = banco.getBoveda("BCP_TRUJILLO");
        b_trujillo->depositar(CodigoActivo::SOLES, 30000);
        Boveda* b_piura = banco.getBoveda("BCP_PIURA");
        b_piura->depositar(CodigoActivo::DOLARES, 10000);
        
    } catch(const OperacionException& e) {
        std::cerr << "Error crítico en la inicialización: " << e.what() << std::endl;
    }
}

void SistemaBancario::mostrarMenu() {
    std::cout << "\n========== MENU PRINCIPAL ==========\n"
              << "1. Ver Reporte Diario\n"
              << "2. Ver Reporte Mensual\n"
              << "3. Ejecutar Operación desde CSV\n"
              << "4. Ver Estado General de Activos\n"
              << "0. Salir\n"
              << "==================================\n"
              << "Ingrese su opción: ";
}

void SistemaBancario::ejecutarOperacionCSV() {
    std::string filename;
    std::cout << "Ingrese el nombre del archivo CSV (ej: solicitud_exitosa.csv): ";
    std::cin >> filename;
    try {
        banco.ejecutarOperacionDesdeCSV(filename, transportador);
    } catch (const OperacionException& e) {
        std::cerr << "\n!!! ERROR EN LA OPERACIÓN: " << e.what() << " !!!\n";
    }
}

void SistemaBancario::mostrarEstadoGeneral() {
    banco.imprimirEstadoGeneral();
    transportador.imprimirEstado();
}

void SistemaBancario::ejecutarReporteDiario() {
    int dia, mes, anio;
    std::cout << "Ingrese fecha (D M AAAA): ";
    std::cin >> dia >> mes >> anio;

    std::cout << "\n--- REPORTE DIARIO: " << dia << "/" << mes << "/" << anio << " ---\n";
    bool encontrado = false;
    for(const auto& reg : banco.getLibroMayor()) {
        std::time_t tt = std::chrono::system_clock::to_time_t(reg.fecha);
        std::tm* tm_info = std::localtime(&tt);
        
        if (tm_info && tm_info->tm_mday == dia && (tm_info->tm_mon + 1) == mes && (tm_info->tm_year + 1900) == anio) {
            imprimirDetalleRegistro(reg);
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No hay operaciones para esta fecha.\n";
}

void SistemaBancario::ejecutarReporteMensual() {
    int mes, anio;
    std::cout << "Ingrese mes y año (M AAAA): ";
    std::cin >> mes >> anio;
    
    std::cout << "\n--- REPORTE MENSUAL: " << mes << "/" << anio << " ---\n";
    bool encontrado = false;
    double saldo_neto = 0;
    for(const auto& reg : banco.getLibroMayor()) {
        std::time_t tt = std::chrono::system_clock::to_time_t(reg.fecha);
        std::tm* tm_info = std::localtime(&tt);

        if (tm_info && (tm_info->tm_mon + 1) == mes && (tm_info->tm_year + 1900) == anio) {
            imprimirDetalleRegistro(reg);
            if(reg.detalle.tipo == TipoParada::ENTREGAR) saldo_neto += reg.detalle.monto;
            else saldo_neto -= reg.detalle.monto;
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No hay operaciones para este mes.\n";
    else std::cout << "\nSaldo neto de operaciones del mes (Entregas - Recojos): " << saldo_neto << std::endl;
}

void SistemaBancario::imprimirDetalleRegistro(const Registro& reg) const {
    std::time_t tt = std::chrono::system_clock::to_time_t(reg.fecha);
    std::tm* tm_info = std::localtime(&tt);

    if (tm_info) {
        std::cout << "------------------------------------------------------\n"
                  << " Fecha: " << std::put_time(tm_info, "%Y-%m-%d %H:%M:%S") << "\n"
                  << " Bóveda: " << reg.boveda_afectada->getCodigo() << "\n"
                  << " Operación: " << tipoParadaToString(reg.detalle.tipo) << "\n"
                  << " Activo: " << codigoActivoToString(reg.detalle.codigo_activo) << "\n"
                  << " Monto: " << std::fixed << std::setprecision(2) << reg.detalle.monto << "\n";
    }
}