#include <iostream>
#include "calculadora.h"
using namespace std;

int main() {
    Calculadora c;  

    int num1, num2, operacion;
    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;
    cout << "Seleccione una opcion: \n  1:Suma\n  2:Resta\n  3:Multiplicacion\n  4:Division\n";
    cin >> operacion;

    switch (operacion) {
        case 1:
            cout << "a + b : " << c.sumar(num1, num2) << endl;
            break;
        case 2:
            cout << "a - b : " << c.restar(num1, num2) << endl;
            break;
        case 3:
            cout << "a * b : " << c.multiplicar(num1, num2) << endl;
            break;
        case 4:
            if (num2 != 0)
                cout << "a / b : " << c.dividir(num1, num2) << endl;
            else
                cout << "No se puede dividir un numero entre cero" << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
    }

    return 0;
}
