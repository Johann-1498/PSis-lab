#include <iostream>
#include <vector>
#include <string>

#include "Suma.h"
#include "Resta.h"
#include "Multiplicacion.h"
#include "Division.h"
#include "Funciones.h"

using namespace std;

int main() {
    int tipo;
    cout << "Tipo de dato:\n1) Numeros\n2) Strings\n3) Vectores\n4) Matrices\nOpcion: ";
    cin >> tipo;

    int op;
    cout << "Operacion:\n1) Suma\n2) Resta\n3) Multiplicacion\n4) Division\nOpcion: ";
    cin >> op;

    try {
        switch (tipo) {
            case 1: {
                int a, b;
                cout << "a b: ";
                cin >> a >> b;
                Operacion<int>* oper = nullptr;
                if      (op == 1) oper = new Suma<int>();
                else if (op == 2) oper = new Resta<int>();
                else if (op == 3) oper = new Multiplicacion<int>();
                else               oper = new Division<int>();
                cout << "Resultado: " << oper->ejecutar(a,b) << "\n";
                delete oper;
                break;
            }
            case 2: {
                cin.ignore();
                string s1, s2;
                cout << "s1: ";
                getline(cin, s1);
                cout << "s2: ";
                getline(cin, s2);
                Operacion<string>* oper = new Suma<string>();
                cout << "Resultado: " << oper->ejecutar(s1, s2) << "\n";
                delete oper;
                break;
            }
            case 3: {
                int n;
                cout << "Tamaño vector: ";
                cin >> n;
                vector<int> v1(n), v2(n);
                cout << "v1: ";
                for (auto& x : v1) cin >> x;
                cout << "v2: ";
                for (auto& x : v2) cin >> x;
                Operacion<vector<int>>* oper = nullptr;
                if      (op == 1) oper = new Suma<vector<int>>();
                else if (op == 2) oper = new Resta<vector<int>>();
                else if (op == 3) oper = new Multiplicacion<vector<int>>();
                else               oper = new Division<vector<int>>();
                auto r = oper->ejecutar(v1, v2);
                cout << "Resultado: ";
                mostrarVector(r);
                cout << "\n";
                delete oper;
                break;
            }
            case 4: {
                int f, c;
                cout << "Filas Columnas: ";
                cin >> f >> c;
                vector<vector<int>> m1(f, vector<int>(c)), m2(f, vector<int>(c));
                cout << "m1:\n";
                for (int i = 0; i < f; ++i)
                    for (int j = 0; j < c; ++j)
                        cin >> m1[i][j];
                cout << "m2:\n";
                for (int i = 0; i < f; ++i)
                    for (int j = 0; j < c; ++j)
                        cin >> m2[i][j];
                Operacion<vector<vector<int>>>* oper = nullptr;
                if      (op == 1) oper = new Suma<vector<vector<int>>>();
                else if (op == 2) oper = new Resta<vector<vector<int>>>();
                else if (op == 3) oper = new Multiplicacion<vector<vector<int>>>();
                else               oper = new Division<vector<vector<int>>>();
                auto R = oper->ejecutar(m1, m2);
                cout << "Resultado:\n";
                mostrarMatriz(R);
                cout << "\n";
                delete oper;
                break;
            }
            default:
                throw runtime_error("Tipo no valido");
        }
    } catch (exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
