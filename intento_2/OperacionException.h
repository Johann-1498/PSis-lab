#pragma once
#include <stdexcept>
#include <string>

class OperacionException : public std::runtime_error {
public:
    explicit OperacionException(const std::string& message)
        : std::runtime_error("[OperacionException] " + message) {}
};