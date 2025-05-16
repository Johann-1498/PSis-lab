#ifndef OPERACION_H
#define OPERACION_H

template<typename T>
class Operacion {
public:
    virtual T ejecutar(const T& a, const T& b) = 0;
    virtual ~Operacion() {}
};

#endif // OPERACION_H
