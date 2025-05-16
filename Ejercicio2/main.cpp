#include <iostream>
#include <vector>
#include "Poligono.h"

int main() {
    std::cout << "CALCULO DE AREAS\n";
    std::cout << "1. Poligono regular\n";
    std::cout << "2. Poligono irregular\n";
    std::cout << "Opcion: ";

    int op;
    std::cin >> op;

    if (op == 1) {
        int n; double lado;
        std::cout << "Numero de lados: "; std::cin >> n;
        std::cout << "Longitud del lado: "; std::cin >> lado;

        PoligonoRegular p(n, lado);
        std::cout << "Area = " << p.area() << "\n";
    }
    else if (op == 2) {
        int n;
        std::cout << "Numero de vertices: "; std::cin >> n;
        std::vector<Punto> verts;
        for (int i = 0; i < n; ++i) {
            double x, y;
            std::cout << "Vertice " << i + 1 << " (x y): ";
            std::cin >> x >> y;
            verts.emplace_back(x, y);
        }
        PoligonoIrregular p(verts);
        std::cout << "Area = " << p.area() << "\n";
    }
    else {
        std::cout << "Opcion no valida.\n";
    }
    return 0;
}
