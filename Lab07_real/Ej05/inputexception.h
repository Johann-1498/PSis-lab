#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include "ComputerException.h"

class InputException : public ComputerException {
public:
    explicit InputException(const std::string& msg) : ComputerException("InputException: " + msg) {}
};

#endif
