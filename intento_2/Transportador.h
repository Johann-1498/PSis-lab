#pragma once

#include <string>
#include <vector>
#include "Activos.h"
#include "OperacionException.h"
#include "TipoOperacion.h"
#include "SolicitudActivos.h"   // <-- ESTA LÍNEA ES LA SOLUCIÓN

// Forward declaration
class Boveda;

// Define una parada en la ruta del transportador
struct ParadaRuta {
    Boveda* boveda;
    TipoOperacion tipo_op;
    SolicitudActivos solicitud; // Ahora el compilador sabe qué es esto
};

class Transportador {
private:
    std::string nombre;
    std::string codigo;
    Activos carga;
    std::vector<ParadaRuta> ruta_actual;

public:
    Transportador(const std::string& n, const std::string& c);
    const std::string& getNombre() const { return nombre; }
    
    void asignarRuta(const std::vector<ParadaRuta>& ruta);
    void ejecutarRuta();
    
    double totalEnCarga() const { return carga.total(); }
};