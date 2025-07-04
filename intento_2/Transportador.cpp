// Transportador.cpp
#include "Transportador.h"
#include "CodigoActivo.h"
#include "ActivosExceptions.h"
#include "TransportadorExceptions.h"
#include "RegistroTransportador.h"
#include "Boveda.h"
#include "Plaza.h"
#include <iostream>

Transportador::Transportador(const std::string& n, const std::string& c) : nombre(n), codigo(c) {}

void Transportador::ejecutarRuta() {
    std::cout << "\n-  Transportador " << nombre << "Inicio de ruta" << std::endl;
    if (ruta.empty()) {
        std::cout << "No hay ruta programada.\n";
        return;
    }
    Boveda* inicio, fin;
    SolicitudActivos solAnterior;
    bool primeraRuta= true;

    for (const auto& parada :ruta) {
        std::cout << "\n-> Camino a la boveda : " << parada.boveda->getCodigo()
                  << " en " << parada.boveda->getPlaza()->ciudad << std::endl;

        try {
            switch (parada.solicitud.tipo_op) {
                case TipoOperacion::RETIRO:
                    std::cout << "   Operacion: Recoger activos" << std::endl;
                    parada.boveda->retirar(parada.solicitud, this);
                    carga.depositar(parada.solicitud);
                    std::cout << "   Exito: Activos recogidos. Carga actual: " << carga.total() << std::endl;

                    if(primeraRuta){
                        inicio=parada.boveda;
                        primeraRuta=false;
                        solAnterior = paradaa.solicitud;
                    }else{
                        fin = parada.boveda;
                        primeraRuta = false;
                        registrarRuta(inicio, fin, solAnterior);
                    }
                
                    break;

                case TipoOperacion::DEPOSITO:
                    std::cout << "   Operacion: Entregar activos." << std::endl;
                    carga.retirar(parada.solicitud.activos);
                    parada.boveda->depositar(parada.solicitud, this);
                    std::cout << "   Exito: Activos entregados. Carga actual: " << carga.total() << std::endl;
                    break;
                
                default:
                    throw OperacionException("Tipo de operación inválida en la ruta del transportador.");
            }
        } catch (const std::exception& e) { 
            ruta_actual.clear();
            throw OperacionException("Fallo en la ruta en la bóveda " + parada.boveda->getCodigo() + ": " + e.what());
        }
    }

    std::cout << "\n--- [Transportador " << nombre << "] RUTA COMPLETADA ---\n";
    if (carga.total() > 0.01) {
         std::cerr << "ADVERTENCIA: El transportador finalizó la ruta con carga residual: " << carga.total() << std::endl;
    }
    ruta_actual.clear();
}


void Transportador::registrarRuta(Boveda* inicio, Boveda* final, const SolicitudActivos& sol){
    // 1) registro de origen
    const Registro& r_or = inicio->getRegistros().back();

    // 2) registro sinterno
    Registro r_tr(TipoOperacion::TRANSFERENCIA, sol,inicio,this);//CORREGIR

    // 3) registro de destino
    const Registro& r_de = final->getRegistros().back();
    // 4) validar y almacenar

    RegistroTransportador reg(r_tr, &r_or, &r_de);

    reg.validar();
    this->registrosTransportador.push_back();
}
