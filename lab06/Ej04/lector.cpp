#include "lector.h"
#include <iostream>
#include <fstream>

using namespace std;

void mostrarArchivoPorBloques(const string& nombreArchivo, int lineasPorBloque) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << nombreArchivo << "'.\n";
        return;
    }

    string linea;
    int contador = 0;

    while (getline(archivo, linea)) {
        cout << linea << endl;
        contador++;

        if (contador % lineasPorBloque == 0) {
            cout << "\nPresiona Enter para continuar...";
            cin.ignore();  // Espera que el usuario presione Enter
        }
    }

    // Si no terminó en múltiplo exacto, aún se debe esperar un Enter final
    if (contador % lineasPorBloque != 0) {
        cout << "\nFin del archivo. Presiona Enter para salir...";
        cin.ignore();
    }

    archivo.close();
}
