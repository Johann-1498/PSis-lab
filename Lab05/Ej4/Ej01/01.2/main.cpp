#include <iostream>
#include "calculadora_zodiaco.h"

int main() {
    FechaNacimiento fecha;
    
    std::cout << "CALCULADORA DE SIGNO ZODIACAL\n";
    std::cout << "Ingrese su fecha de nacimiento (dd mm aaaa): ";
    std::cin >> fecha.dia >> fecha.mes >> fecha.año;
    
    double posicion_solar = calcularPosicionSolar(fecha);
    std::string signo = determinarSignoZodiacal(posicion_solar);
    
    std::cout << "\nRESULTADOS:\n";
    std::cout << "- Signo zodiacal: " << signo << "\n";
    
    return 0;
}