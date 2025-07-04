#pragma once
#include "OperacionException.h"
#include <string>

class CSVException : public OperacionException {
public:
    explicit CSVException(const std::string& message) : OperacionException("[CSV Error] " + message) {}
};

class ArchivoNoEncontradoException : public CSVException {
public:
    explicit ArchivoNoEncontradoException(const std::string& ruta);
};

class FormatoCSVInvalidoException : public CSVException {
public:
    explicit FormatoCSVInvalidoException(int linea, const std::string& detalle);
};