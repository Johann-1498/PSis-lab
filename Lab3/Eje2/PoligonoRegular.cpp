#include "PoligonoRegular.h"
#include <iostream>

PoligonoRegular::PoligonoRegular(int lados, double longitud): longLado(longitud){
    numLados = static_cast<double>(lados);
    area      = 0.0;
}

void PoligonoRegular::calcularArea() {
    if (numLados < 3 || longLado <= 0.0) { //No es un poligono valido
        area = 0.0;
    
    } else if (numLados == 3) {        //(√3 / 4) * l^2
        area = (std::sqrt(3.0) / 4.0) * longLado * longLado;
    
    } else if (numLados == 4) {  //l^2
        area = longLado * longLado;
    }
    else {//Fórmula genérica
        area = (numLados * longLado * longLado) / (4.0 * std::tan(PI / numLados));
    }
}

void PoligonoRegular::print() const {
    double perimetro = numLados * longLado;
    std::cout
        << "---------POLIGONO---REGULAR------------------\n"
        << "- Lados: " << getNumLados() << "\n"
        << "- Perimetro : " << perimetro << "\n"
        << "- Area: " << getArea() << "\n";
}
