#ifndef RESISTENCIA_H
#define RESISTENCIA_H
class Resistencia {
    private:
        float valor; //ohmios
    public:
        Resistencia(float r = 0);
        float getValor() const;
        void setValor(float r);
};
#endif
