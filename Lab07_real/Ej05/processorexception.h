#ifndef PROCESSOR_EXCEPTION_H
#define PROCESSOR_EXCEPTION_H

#include "ComputerException.h"

class ProcessorException : public ComputerException {
public:
    explicit ProcessorException(const std::string& msg) : ComputerException("ProcessorException: " + msg) {}
};

#endif
