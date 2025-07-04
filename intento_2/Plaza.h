// Plaza.h
#pragma once
#include <string>
#include <vector>
#include "TransportadorExceptions.h"
class Boveda;
struct SolicitudActivos;
class Plaza {
public:
    std::string ciudad;
    std::string codigo;
    std::vector<ParadaRuta> rutas; 

    explicit Plaza(const std::string& ciudad) 
        : ciudad(ciudad) {}
    
    void asignarRuta(const std::vector<ParadaRuta>& ruta){
        if (!ruta_actual.empty()) {
        throw RutaActivaException();
        }
        if (ruta.empty()) {
            throw RutaInvalidaException();
        }
        std::cout << "Ruta asignada con " << ruta.size() << " paradas.\n";
    }
        
};

// Define una parada en la ruta del transportador
struct ParadaRuta {
    Boveda* boveda;
    SolicitudActivos solicitud;
};
