#pragma once
#include "OperacionException.h"
#include <string>

class BancoException : public OperacionException {
public:
    explicit BancoException(const std::string& msg) : OperacionException("[Banco] " + msg) {}
};

class BovedaNoEncontradaException : public BancoException {
public:
    explicit BovedaNoEncontradaException(const std::string& codigo_boveda);
};