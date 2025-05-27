#include "facturacion.h"
#include <iostream>
#include <iomanip>

using namespace std;

void mostrarClientes(const vector<Cliente>& clientes) {
    cout << "\nLISTA DE CLIENTES\n";
    cout << left << setw(20) << "Nombre"
         << setw(10) << "Unidades"
         << setw(15) << "Precio Unit."
         << setw(15) << "Total"
         << setw(15) << "Estado" << endl;
    cout << string(75, '-') << endl;
    
    for (const auto& cliente : clientes) {
        cliente.mostrarInformacion();
    }
}

void agregarCliente(vector<Cliente>& clientes) {
    Cliente nuevoCliente;
    
    cout << "\nAGREGAR NUEVO CLIENTE\n";
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, nuevoCliente.nombre);
    
    cout << "Unidades: ";
    cin >> nuevoCliente.unidades;
    
    cout << "Precio unitario: ";
    cin >> nuevoCliente.precioUnitario;
    
    cout << "Estado (0-Moroso, 1-Atrasado, 2-Pagado): ";
    int estado;
    cin >> estado;
    nuevoCliente.estado = static_cast<EstadoPago>(estado);
    
    clientes.push_back(nuevoCliente);
    cout << "Cliente agregado exitosamente!\n";
}

void generarFactura(const Cliente& cliente) {
    cout << "\nFACTURA PARA: " << cliente.nombre << "\n";
    cout << "--------------------------------\n";
    cout << "Unidades: " << cliente.unidades << "\n";
    cout << "Precio unitario: $" << fixed << setprecision(2) << cliente.precioUnitario << "\n";
    cout << "Total: $" << cliente.getTotal() << "\n";
    cout << "Estado: " << cliente.estadoToString() << "\n";
    cout << "--------------------------------\n\n";
}

double calcularTotalFacturado(const vector<Cliente>& clientes) {
    double total = 0.0;
    for (const auto& cliente : clientes) {
        total += cliente.getTotal();
    }
    return total;
}

void mostrarResumen(const vector<Cliente>& clientes) {
    int morosos = 0, atrasados = 0, pagados = 0;
    
    for (const auto& cliente : clientes) {
        switch(cliente.estado) {
            case EstadoPago::MOROSO: morosos++; break;
            case EstadoPago::ATRASADO: atrasados++; break;
            case EstadoPago::PAGADO: pagados++; break;
        }
    }
    
    cout << "\nRESUMEN DE FACTURACION\n";
    cout << "Clientes totales: " << clientes.size() << "\n";
    cout << "Clientes morosos: " << morosos << "\n";
    cout << "Clientes atrasados: " << atrasados << "\n";
    cout << "Clientes pagados: " << pagados << "\n";
    cout << "Total facturado: $" << fixed << setprecision(2) 
         << calcularTotalFacturado(clientes) << "\n";
}

void mostrarClientesMorosos(const vector<Cliente>& clientes) {
    cout << "\nCLIENTES MOROSOS\n";
    cout << left << setw(20) << "Nombre"
         << setw(10) << "Unidades"
         << setw(15) << "Precio Unit."
         << setw(15) << "Total"
         << setw(15) << "Estado" << endl;
    cout << string(75, '-') << endl;
    
    for (const auto& cliente : clientes) {
        if (cliente.estado == EstadoPago::MOROSO) {
            cliente.mostrarInformacion();
        }
    }
}

void mostrarClientesPagadosConMontoMayorA(const vector<Cliente>& clientes, double montoMinimo) {
    cout << "\nCLIENTES PAGADOS CON FACTURA MAYOR A $" << montoMinimo << "\n";
    cout << left << setw(20) << "Nombre"
         << setw(10) << "Unidades"
         << setw(15) << "Precio Unit."
         << setw(15) << "Total"
         << setw(15) << "Estado" << endl;
    cout << string(75, '-') << endl;
    
    for (const auto& cliente : clientes) {
        if (cliente.estado == EstadoPago::PAGADO && cliente.getTotal() > montoMinimo) {
            cliente.mostrarInformacion();
        }
    }
}

void cambiarEstadoCliente(vector<Cliente>& clientes) {
    if (clientes.empty()) {
        cout << "No hay clientes registrados.\n";
        return;
    }

    mostrarClientes(clientes);
    
    int indice;
    cout << "Seleccione el número del cliente a modificar (0-" << clientes.size()-1 << "): ";
    cin >> indice;
    
    if (indice < 0 || indice >= clientes.size()) {
        cout << "Índice inválido.\n";
        return;
    }

    int nuevoEstado;
    cout << "Seleccione el nuevo estado:\n";
    cout << "0 - Moroso\n";
    cout << "1 - Atrasado\n";
    cout << "2 - Pagado\n";
    cout << "Opción: ";
    cin >> nuevoEstado;

    if (nuevoEstado < 0 || nuevoEstado > 2) {
        cout << "Estado inválido.\n";
        return;
    }

    clientes[indice].estado = static_cast<EstadoPago>(nuevoEstado);
    cout << "Estado actualizado correctamente.\n";
    cout << "Nuevos datos del cliente:\n";
    clientes[indice].mostrarInformacion();
}