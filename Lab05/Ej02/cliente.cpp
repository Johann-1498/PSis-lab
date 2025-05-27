#include "cliente.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Métodos de la estructura Cliente
double Cliente::getTotal() const { 
    return unidades * precioUnitario; 
}

string Cliente::estadoToString() const {
    switch(estado) {
        case EstadoPago::MOROSO: return "Moroso";
        case EstadoPago::ATRASADO: return "Atrasado";
        case EstadoPago::PAGADO: return "Pagado";
        default: return "Desconocido";
    }
}

void Cliente::mostrarInformacion() const {
    cout << left << setw(20) << nombre
         << setw(10) << unidades
         << setw(15) << fixed << setprecision(2) << precioUnitario
         << setw(15) << getTotal()
         << setw(15) << estadoToString() << endl;
}