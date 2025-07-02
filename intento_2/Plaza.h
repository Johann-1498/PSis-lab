// Plaza.h
#pragma once
#include <string>

class Plaza {
public:
    std::string ciudad;
    std::string direccion;
    std::string codigo;

    explicit Plaza(const std::string& ciudad) 
        : ciudad(ciudad) {}
};