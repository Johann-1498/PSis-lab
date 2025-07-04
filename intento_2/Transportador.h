#pragma once

#include <string>
#include <vector>
#include "Activos.h"
#include "OperacionException.h"
#include "TipoOperacion.h"
#include "SolicitudActivos.h"   // <-- ESTA LÍNEA ES LA SOLUCIÓN
#include "Plaza.h"
#include "Registro.h"
#include "Boveda.h"
#include "TransportadorExceptions.h"
#include "RegistroTransportador.h"

class Plaza;
class Transportador {
private:
    std::string nombre;
    Activos carga;
    Plaza ruta;
    std::vector<RegistroTransportador> registrosTransportador;

public:
    Transportador(const std::string& n, const std::string& c);
    
    const std::string& getNombre() const { return nombre; }
    void ejecutarRuta();
    double totalEnCarga() const { return carga.total(); }

    void registrarRuta(Boveda* inicio, Boveda* final, Activos activos){

    }


};


