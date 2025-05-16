#include "Poligono.h"
#include <cmath>
#include <corecrt_math_defines.h>

double PoligonoRegular::calcularArea(){
    double area = (lados*longitud*longitud)/(4*tan(M_PI/lados));
    return area;
}

double PoligonoIrregular::calcularArea(){

    for(){
    Punto p1 = vertices[i];
    Punto p2 = vertices[i+1];
    }
}