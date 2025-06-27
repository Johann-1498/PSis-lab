#ifndef COMPUTER_EXCEPTION_H
#define COMPUTER_EXCEPTION_H

#include <string>
#include <stdexcept>

class ComputerException : public std::exception {
protected:
    std::string message;

public:
    explicit ComputerException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif
