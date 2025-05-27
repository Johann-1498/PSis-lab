#ifndef FACTURACION_H
#define FACTURACION_H

#include <vector>
#include "cliente.h"

using namespace std;

void mostrarClientes(const vector<Cliente>& clientes);
void agregarCliente(vector<Cliente>& clientes);
void generarFactura(const Cliente& cliente);
double calcularTotalFacturado(const vector<Cliente>& clientes);
void mostrarResumen(const vector<Cliente>& clientes);
void mostrarClientesMorosos(const vector<Cliente>& clientes);
void mostrarClientesPagadosConMontoMayorA(const vector<Cliente>& clientes, double montoMinimo);
void cambiarEstadoCliente(vector<Cliente>& clientes);

#endif