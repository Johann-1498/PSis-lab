#ifndef RESISTENCIA_H
#define RESISTENCIA_H
class Resistencia {
private:
    float valor; // en ohmios puede (colocar con . )
public:
    Resistencia(float r = 0);
    float getValor() const;
    void setValor(float r);
};
#endif
