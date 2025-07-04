#include "CSVParser.h"
#include "excepciones/CSVExceptions.h"
#include <fstream>
#include <sstream>

ArchivoNoEncontradoException::ArchivoNoEncontradoException(const std::string& ruta) : CSVException("No se pudo abrir el archivo: " + ruta) {}
FormatoCSVInvalidoException::FormatoCSVInvalidoException(int linea, const std::string& detalle) : CSVException("Formato inválido en la línea " + std::to_string(linea) + ": " + detalle) {}

std::vector<ParadaRuta> CSVParser::parse(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) throw ArchivoNoEncontradoException(nombre_archivo);

    std::vector<ParadaRuta> ruta;
    std::string linea;
    int numero_linea = 1;
    std::getline(archivo, linea);

    while (std::getline(archivo, linea)) {
        numero_linea++;
        std::stringstream ss(linea);
        std::string campo;
        ParadaRuta p;

        if (!std::getline(ss, p.codigo_boveda, ',')) throw FormatoCSVInvalidoException(numero_linea, "Falta código de bóveda");
        
        std::getline(ss, campo, ',');
        if (campo == "RECOGER") p.tipo = TipoParada::RECOGER;
        else if (campo == "ENTREGAR") p.tipo = TipoParada::ENTREGAR;
        else throw FormatoCSVInvalidoException(numero_linea, "Tipo de operación inválido: " + campo);

        std::getline(ss, campo, ',');
        if (campo == "SOLES") p.codigo_activo = CodigoActivo::SOLES;
        else if (campo == "DOLARES") p.codigo_activo = CodigoActivo::DOLARES;
        else if (campo == "BONO") p.codigo_activo = CodigoActivo::BONO;
        else throw FormatoCSVInvalidoException(numero_linea, "Tipo de activo inválido: " + campo);

        if (!(ss >> p.monto)) throw FormatoCSVInvalidoException(numero_linea, "Monto inválido");
        ruta.push_back(p);
    }
    return ruta;
}