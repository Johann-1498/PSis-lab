#include <iostream>
using namespace std;

// Declaración de funciones
double AreaCuadrilatero(double lado_a, double lado_b);
double AreaTriangulo(double base, double altura);

// Programa principal
int main() {
    double a, b;
    int figura;
    
    cout << "Que figura quiere analizar, Cuadrado (1), Rectangulo(2), Triangulo(3):" << endl;
    cin >> figura;

    switch (figura) {
        case 1:
            cout << "Introduzca el valor del lado: " << endl;
            cin >> a;
            cout << "El area del cuadrado es: " << AreaCuadrilatero(a, a) << endl;
            break;
            
        case 2:
            cout << "Introduzca el valor del lado a y b: " << endl;
            cin >> a >> b;
            cout << "El area del rectangulo es: " << AreaCuadrilatero(a, b) << endl;
            break;
            
        case 3:
            cout << "Introduzca la base y la altura: " << endl;
            cin >> a >> b;
            cout << "El area del triangulo es: " << AreaTriangulo(a, b) << endl;
            break;
            
        default:
            cout << "Figura no reconocida" << endl;
            break;
    }
    
    return 0;
}

// Definición de funciones
double AreaCuadrilatero(double lado_a, double lado_b) {
    if (lado_a <= 0 || lado_b <= 0) {
        cout << "Error: Los lados deben ser positivos" << endl;
        return -1;
    }
    return lado_a * lado_b;
}

double AreaTriangulo(double base, double altura) {
    if (base <= 0 || altura <= 0) {
        cout << "Error: La base y altura deben ser positivas" << endl;
        return -1;
    }
    return (base * altura) / 2;
}