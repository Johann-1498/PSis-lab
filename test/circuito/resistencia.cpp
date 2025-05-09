#include "resistencia.h"
//constructor
Resistencia::Resistencia(float r) : valor(r) {}
//getter y setter
float Resistencia::getValor() const {
    return valor;
}
void Resistencia::setValor(float r) {
    valor = r;
}
