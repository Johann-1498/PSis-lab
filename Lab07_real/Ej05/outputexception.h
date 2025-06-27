#ifndef OUTPUT_EXCEPTION_H
#define OUTPUT_EXCEPTION_H

#include "ComputerException.h"

class OutputException : public ComputerException {
public:
    explicit OutputException(const std::string& msg) : ComputerException("OutputException: " + msg) {}
};

#endif
