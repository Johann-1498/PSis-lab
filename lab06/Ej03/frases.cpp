#include "frases.h"
#include <iostream>
#include <fstream>

using namespace std;

void escribirFrasesEnArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }

    string frase;
    cout << "Introduce frases (presiona Enter sin escribir nada para terminar):\n";

    while (true) {
        getline(cin, frase);
        if (frase.empty()) break;
        archivo << frase << endl;
    }

    archivo.close();
}

void mostrarContenidoDelArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para lectura.\n";
        return;
    }

    string linea;
    cout << "\nContenido del archivo '" << nombreArchivo << "':\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}
