#include <iostream>
#include "Transportador.h"
#include "TransportadorExceptions.h"

int main() {
    Transportador transportador("TRANSPORTADOR_1"); // Asumiendo que necesita nombre
    std::vector<ParadaRuta> ruta = {{"LOCACION_A"}, {"LOCACION_B"}};
    
    transportador.asignarRuta(ruta);
    std::cout << "Ruta asignada correctamente (primera vez)" << std::endl;
    
    try {
        std::cout << "Intentando asignar segunda ruta..." << std::endl;
        transportador.asignarRuta(ruta);
    } catch (const RutaActivaException& e) {
        std::cerr << "✅ Excepción capturada correctamente:\n" << e.what() << std::endl;
    }
    return 0;
}