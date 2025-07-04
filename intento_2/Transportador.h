#pragma once
#include <string>
#include <vector>
#include "Activos.h"

class Banco;
class Registro;
struct ParadaRuta;

class Transportador {
private:
    std::string nombre;
    Activos carga;
    void limpiarCarga();
public:
    Transportador(const std::string& nombre);
    std::vector<Registro> ejecutarRuta(const std::vector<ParadaRuta>& ruta, Banco* banco_contexto);
    void imprimirEstado() const;
};