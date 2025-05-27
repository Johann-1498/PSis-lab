#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TORRES = 7;
const int PISOS = 20;
const int DEPTOS = 6;

void cargarHabitantes(int* complejo, int modo) {
    int valor;
    if (modo == 2) {
        cout << "Ingrese valor predeterminado por departamento: ";
        cin >> valor;
    } else if (modo == 3) {
        srand(time(0));
    }

    for (int t = 0; t < TORRES; t++) {
        for (int p = 0; p < PISOS; p++) {
            for (int d = 0; d < DEPTOS; d++) {
                int idx = t * PISOS * DEPTOS + p * DEPTOS + d;
                if (modo == 1) {
                    cout << "Torre " << t + 1 << ", Piso " << p + 1 << ", Dpto " << d + 1 << ": ";
                    cin >> *(complejo + idx);
                } else if (modo == 2) {
                    *(complejo + idx) = valor;
                } else if (modo == 3) {
                    *(complejo + idx) = rand() % 6 + 1;
                }
            }
        }
    }
}

int totalHabitantes(int* complejo) {
    int total = 0;
    for (int t = 0; t < TORRES; t++)
        for (int p = 0; p < PISOS; p++)
            for (int d = 0; d < DEPTOS; d++)
                total += *(complejo + t * PISOS * DEPTOS + p * DEPTOS + d);
    return total;
}

void promedioPorPiso(int* complejo) {
    for (int t = 0; t < TORRES; t++) {
        cout << "\nPromedios por piso - Torre " << t + 1 << ":\n";
        for (int p = 0; p < PISOS; p++) {
            int suma = 0;
            for (int d = 0; d < DEPTOS; d++) {
                suma += *(complejo + t * PISOS * DEPTOS + p * DEPTOS + d);
            }
            double promedio = (double)suma / DEPTOS;
            cout << "  Piso " << p + 1 << ": " << promedio << "\n";
        }
    }
}

void promedioPorTorre(int* complejo) {
    for (int t = 0; t < TORRES; t++) {
        int suma = 0;
        for (int p = 0; p < PISOS; p++)
            for (int d = 0; d < DEPTOS; d++)
                suma += *(complejo + t * PISOS * DEPTOS + p * DEPTOS + d);
        double promedio = (double)suma / (PISOS * DEPTOS);
        cout << "Torre " << t + 1 << ": " << promedio << "\n";
    }
}

int main() {
    int complejo[TORRES][PISOS][DEPTOS];
    int modo;

    cout << "Seleccione modo:\n1 - Manual\n2 - Valor fijo\n3 - Aleatorio\nOpción: ";
    cin >> modo;
    if (modo < 1 || modo > 3) {
        cout << "Modo no válido.\n";
        return 1;
    }

    cargarHabitantes(&complejo[0][0][0], modo);

    cout << "\n(a) Total de habitantes: " << totalHabitantes(&complejo[0][0][0]) << "\n";
    cout << "\n(b) Promedios por piso:\n";
    promedioPorPiso(&complejo[0][0][0]);
    cout << "\n(c) Promedios por torre:\n";
    promedioPorTorre(&complejo[0][0][0]);

    return 0;
}
