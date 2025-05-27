#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

enum class EstadoPago { MOROSO, ATRASADO, PAGADO };

struct Cliente {
    string nombre;
    int unidades;
    double precioUnitario;
    EstadoPago estado;

    // Metodos
    double getTotal() const;
    string estadoToString() const;
    void mostrarInformacion() const;
};

#endif