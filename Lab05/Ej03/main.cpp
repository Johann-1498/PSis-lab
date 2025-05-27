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
    cout << "5. Mostrar clientes morosos\n";
    cout << "6. Mostrar clientes pagados con monto mayor a X\n";
    cout << "7. Cambiar estado de cliente\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    vector<Cliente> clientes = {
        {"Juan Ramirez", 10, 15.50, EstadoPago::PAGADO},
        {"Maria Pardo", 5, 22.05, EstadoPago::ATRASADO},
        {"Carlos Diaz", 8, 12.50, EstadoPago::MOROSO},
        {"Ana Lopez", 20, 30.00, EstadoPago::PAGADO},
        {"Pedro Gomez", 3, 10.00, EstadoPago::MOROSO}
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
                cout << "Ingrese el índice del cliente: ";
                cin >> indice;
                if (indice >= 0 && indice < clientes.size()) {
                    generarFactura(clientes[indice]);
                } else {
                    cout << "Índice inválido!\n";
                }
                break;
            }
            case 4:
                mostrarResumen(clientes);
                break;
            case 5:
                mostrarClientesMorosos(clientes);
                break;
            case 6: {
                double montoMinimo;
                cout << "Ingrese el monto mínimo: ";
                cin >> montoMinimo;
                mostrarClientesPagadosConMontoMayorA(clientes, montoMinimo);
                break;
            }
            case 7:
                cambiarEstadoCliente(clientes);
                break;
            case 8:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción inválida!\n";
        }
    } while (opcion != 8);

    return 0;
}