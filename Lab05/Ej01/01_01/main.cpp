#include <iostream>
#include "fecha.h"
#include <stdexcept>

using namespace std;

int main() {
    Fecha fecha1, fecha2;
    
    cout << "Calculadora de dias entre dos fechas" << endl;
    cout << "----------------------------------" << endl;
    
    try {
        // Solicitar primera fecha
        cout << "\nIngrese la primera fecha (dd mm aaaa): ";
        cin >> fecha1.dia >> fecha1.mes >> fecha1.anio;
        
        if (!fechaValida(fecha1)) {
            throw invalid_argument("La primera fecha no es valida");
        }
        
        // Solicitar segunda fecha
        cout << "Ingrese la segunda fecha (dd mm aaaa): ";
        cin >> fecha2.dia >> fecha2.mes >> fecha2.anio;
        
        if (!fechaValida(fecha2)) {
            throw invalid_argument("La segunda fecha no es valida");
        }
        
        // Calcular diferencia
        long diferencia = diferenciaDias(fecha1, fecha2);
        
        // Mostrar resultado
        cout << "\nHay " << abs(diferencia) << " dias entre " 
             << fecha1.dia << "/" << fecha1.mes << "/" << fecha1.anio 
             << " y " 
             << fecha2.dia << "/" << fecha2.mes << "/" << fecha2.anio 
             << endl;
             
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}