#pragma once
#include <stdexcept>
#include <string>

// Excepción personalizada para errores en las operaciones del banco/transportador
class OperacionException : public std::runtime_error {
public:
    explicit OperacionException(const std::string& message)
        : std::runtime_error(message) {}
};