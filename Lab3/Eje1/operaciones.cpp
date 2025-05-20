#include <iostream>
using namespace std;

// Declaración de funciones de las operaciones
int sumar(int a, int b) { return a + b; }
int restar(int a, int b) { return a - b; }
int multiplicar(int a, int b) { return a * b; }
double dividir(int a, int b) { return static_cast<double>(a) / b; }

int main() {
    int num1, num2;
    int operacion;

    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;
    cout << "Seleccione una opcion: ";
    cout << "\n  1:Suma\n  2:Resta\n  3:Multiplicacion\n  4:Division";
    cout << "\nIngrese una opcion: ";
    cin >> operacion;

    // Uso de las funciones según la operación indicada
    switch (operacion) {
        case 1:
            cout << "a + b : " << sumar(num1, num2) << endl;
            break;
        case 2:
            cout << "a - b : " << restar(num1, num2) << endl;
            break;
        case 3:
            cout << "a * b : " << multiplicar(num1, num2) << endl;
            break;
        case 4:
            if (num2 != 0)
                cout << "a / b : " << dividir(num1, num2) << endl;
            else
                cout << "No se puede dividir un numero entre cero" << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
    }

    return 0;
}
