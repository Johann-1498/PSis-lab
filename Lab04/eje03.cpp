#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TORRES = 7;
const int PISOS = 20;
const int DEPARTAMENTOS = 6;

void cargarHabitantes(int complejo[TORRES][PISOS][DEPARTAMENTOS], int modo) {
    int valor_predeterminado = 0;

    if (modo == 2) {
        cout << "Ingrese el número de personas predeterminado por departamento: ";
        cin >> valor_predeterminado;
    } else if (modo == 3) {
        srand(time(0));  // Semilla para números aleatorios
    }

    for (int t = 0; t < TORRES; t++) {
        for (int p = 0; p < PISOS; p++) {
            for (int d = 0; d < DEPARTAMENTOS; d++) {
                if (modo == 1) {
                    cout << "Torre " << t + 1 << ", Piso " << p + 1 << ", Dpto " << d + 1 << ": ";
                    cin >> complejo[t][p][d];
                } else if (modo == 2) {
                    complejo[t][p][d] = valor_predeterminado;
                } else if (modo == 3) {
                    complejo[t][p][d] = rand() % 6 + 1;  // de 1 a 6 personas
                }
            }
        }
    }
}

int totalHabitantes(int complejo[TORRES][PISOS][DEPARTAMENTOS]) {
    int total = 0;
    for (int t = 0; t < TORRES; t++)
        for (int p = 0; p < PISOS; p++)
            for (int d = 0; d < DEPARTAMENTOS; d++)
                total += complejo[t][p][d];
    return total;
}

void promedioPorPiso(int complejo[TORRES][PISOS][DEPARTAMENTOS]) {
    for (int t = 0; t < TORRES; t++) {
        cout << "\nPromedios por piso - Torre " << t + 1 << ":\n";
        for (int p = 0; p < PISOS; p++) {
            int suma = 0;
            for (int d = 0; d < DEPARTAMENTOS; d++) {
                suma += complejo[t][p][d];
            }
            double promedio = (double)suma / DEPARTAMENTOS;
            cout << "  Piso " << p + 1 << ": " << promedio << " habitantes por departamento\n";
        }
    }
}

void promedioPorTorre(int complejo[TORRES][PISOS][DEPARTAMENTOS]) {
    for (int t = 0; t < TORRES; t++) {
        int suma = 0;
        for (int p = 0; p < PISOS; p++)
            for (int d = 0; d < DEPARTAMENTOS; d++)
                suma += complejo[t][p][d];
        double promedio = (double)suma / (PISOS * DEPARTAMENTOS);
        cout << "Torre " << t + 1 << ": " << promedio << " habitantes por departamento\n";
    }
}

int main() {
    int complejo[TORRES][PISOS][DEPARTAMENTOS];
    int modo;

    cout << "Seleccione modo de carga de datos:\n";
    cout << "1 - Manual (por departamento)\n";
    cout << "2 - Automático (valor predeterminado por departamento)\n";
    cout << "3 - Automático aleatorio (1 a 6 personas por dpto)\n";
    cout << "Opción: ";
    cin >> modo;

    if (modo < 1 || modo > 3) {
        cout << "Modo no válido.\n";
        return 1;
    }

    cargarHabitantes(complejo, modo);

    // Resultados
    int total = totalHabitantes(complejo);
    cout << "\n(a) Total de habitantes: " << total << "\n";

    cout << "\n(b) Promedio de habitantes por piso de cada torre:\n";
    promedioPorPiso(complejo);

    cout << "\n(c) Promedio de habitantes por torre:\n";
    promedioPorTorre(complejo);

    return 0;
}
