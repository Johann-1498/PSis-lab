#include "Banco.h"
#include "Boveda.h"
#include "Transportador.h"
#include "CSVParser.h"
#include "Registro.h"
#include "excepciones/BancoExceptions.h"
#include <iostream>

BovedaNoEncontradaException::BovedaNoEncontradaException(const std::string& codigo_boveda)
    : BancoException("Bóveda no encontrada: " + codigo_boveda) {}

Banco::Banco(const std::string& nombre) : nombre(nombre) {}
Banco::~Banco() = default;

void Banco::agregarBoveda(const std::string& codigo, Plaza* p) { bovedas.emplace_back(std::make_unique<Boveda>(codigo, p)); }
const std::vector<Registro>& Banco::getLibroMayor() const { return libro_mayor; }

Boveda* Banco::getBoveda(const std::string& codigo) {
    for (const auto& b : bovedas) {
        if (b->getCodigo() == codigo) return b.get();
    }
    throw BovedaNoEncontradaException(codigo);
}

void Banco::ejecutarOperacionDesdeCSV(const std::string& archivo, Transportador& transportador) {
    std::cout << "\n>>> [Banco " << nombre << "] Procesando solicitud desde " << archivo << " <<<\n";
    CSVParser parser;
    std::vector<ParadaRuta> ruta = parser.parse(archivo);
    
    auto registros_generados = transportador.ejecutarRuta(ruta, this);
    
    libro_mayor.insert(libro_mayor.end(), registros_generados.begin(), registros_generados.end());
    std::cout << ">>> Operación completada y registrada en el libro mayor del banco. <<<\n";
}

void Banco::imprimirEstadoGeneral() const {
    std::cout << "\n--- ESTADO GENERAL DEL BANCO: " << nombre << " ---\n";
    for (const auto& b : bovedas) {
        std::cout << "\n  Bóveda: " << b->getCodigo() << "\n";
        b->imprimirEstado();
    }
    std::cout << "--------------------------------------\n";
}