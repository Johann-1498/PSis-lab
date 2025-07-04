#pragma once
#include "Banco.h"
#include "Transportador.h"
#include "Registro.h"

class SistemaBancario {
private:
    Banco banco;
    Transportador transportador;

    void mostrarMenu();
    void ejecutarReporteDiario();
    void ejecutarReporteMensual();
    void ejecutarOperacionCSV();
    void mostrarEstadoGeneral();
    void poblarDatosIniciales();
    void imprimirDetalleRegistro(const Registro& reg) const;

public:
    SistemaBancario();
    void run();
};