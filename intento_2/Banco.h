#pragma once
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Boveda;
class Plaza;
class Transportador;
class Registro; // <-- Se declara pero no se incluye

class Banco {
private:
    std::string nombre;
    std::vector<std::unique_ptr<Boveda>> bovedas;
    std::vector<Registro> libro_mayor; // <-- Contenedor de tipo incompleto
public:
    explicit Banco(const std::string& nombre);
    ~Banco();

    void agregarBoveda(const std::string& codigo, Plaza* p);
    Boveda* getBoveda(const std::string& codigo);
    void ejecutarOperacionDesdeCSV(const std::string& archivo, Transportador& transportador);
    const std::vector<Registro>& getLibroMayor() const;
    void imprimirEstadoGeneral() const;
};