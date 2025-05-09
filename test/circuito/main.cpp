#include <iostream>
#include "circuito.h"
using namespace std;
//menu de ingreso de datos
void mostrarMenu() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Establecer tension(V)" << endl;
    cout << "2. Agregar resistencia(R)" << endl;
    cout << "3. Mostrar resistencias(R)" << endl;
    cout << "4. Calcular y mostrar resultados(I)" << endl;
    cout << "5. Eliminar todas las resistencias(I)" << endl;
    cout << "0. Salir" << endl;
    cout << "======================" << endl;
    cout << "Seleccione una opcion: ";
}
int main() {
    Circuito circuito;
    int opcion;
    float valor;
    cout << "Calculadora avanzada de circuitos electricos" << endl;
    do {
        mostrarMenu();
        cin >> opcion;
        switch(opcion) {
            case 1:
                cout << "Ingrese la tension en voltios (V): ";
                cin >> valor;
                circuito.setTension(valor);
                cout << "Tension establecida correctamente." << endl;
                break;
            case 2:
                do {
                    cout << "Ingrese el valor de la resistencia en ohmios (Ω) (0 para terminar): ";
                    cin >> valor;
                    if (valor != 0) {
                        circuito.agregarResistencia(valor);
                        cout << "Resistencia agregada correctamente." << endl;
                    }
                } while (valor != 0);
                break;
            case 3:
                circuito.mostrarResistencias();
                break;
            case 4:
                circuito.mostrarResultados();
                break;
            case 5:
                circuito.eliminarResistencias();
                cout << "Todas las resistencias han sido eliminadas." << endl;
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;  
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 0);  
    return 0;
}
