#ifndef CIRCUITO_H
#define CIRCUITO_H
#include "resistencia.h"
#include <vector>
using namespace std;


class Circuito {
private:
    float tension;
    vector<Resistencia*> resistencias;
public:
    Circuito(float v = 0);
    ~Circuito();

    void setTension(float v);
    void agregarResistencia(float r);
    void eliminarResistencias();
   
    float calcularResistenciaSerie() const;
    float calcularResistenciaParalelo() const;
    float calcularCorrienteSerie() const;
    float calcularCorrienteParalelo() const;
   
    void mostrarResultados() const;
    void mostrarResistencias() const;
};
#endif
