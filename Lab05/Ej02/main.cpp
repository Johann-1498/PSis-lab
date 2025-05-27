#include <iostream>
#include <vector>
#include "cliente.h"
#include "facturacion.h"

using namespace std;

void mostrarMenu() {
    cout << "\nSISTEMA DE FACTURACION\n";
    cout << "1. Mostrar clientes\n";
    cout << "2. Agregar cliente\n";
    cout << "3. Generar factura\n";
    cout << "4. Mostrar resumen\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    vector<Cliente> clientes = {
        {"Juan Ramirez", 10, 15.50, EstadoPago::PAGADO},
        {"Maria Pardo", 5, 22.05, EstadoPago::ATRASADO},
        {"Carlos Diaz", 8, 12.50, EstadoPago::MOROSO}
    };

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarClientes(clientes);
                break;
            case 2:
                agregarCliente(clientes);
                break;
            case 3: {
                int indice;
                cout << "Ingrese el indice del cliente: ";
                cin >> indice;
                if (indice >= 0 && indice < clientes.size()) {
                    generarFactura(clientes[indice]);
                } else {
                    cout << "Indice invalido!\n";
                }
                break;
            }
            case 4:
                mostrarResumen(clientes);
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción invalida!\n";
        }
    } while (opcion != 5);

    return 0;
}