#pragma once
#include <string>

class Plaza {
public:
    explicit Plaza(const std::string& ciudad) : ciudad(ciudad) {}

    std::string ciudad;
    std::string direccion;
    std::string codigo;
};