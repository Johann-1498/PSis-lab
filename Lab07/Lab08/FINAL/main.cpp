#include <iostream>
#include <unordered_map>
#include "Reader.h"
#include "usuario.h"
#include "cancion.h"
#include "RankingCanciones.h"
#include "lsh.h"
#include "Rendimiento.h"

using namespace std;

void sistemaRecomendaciones(LSH& sistema) {
    int consultaID;
    cout << "\n👤 Ingresa ID de usuario para buscar similares (-1 para salir): ";
    cin >> consultaID;

    while (consultaID != -1) {
        sistema.buscarSimilares(consultaID);
        cout << "\n👤 Ingresa otro ID (-1 para salir): ";
        cin >> consultaID;
    }
}

int obtenerMaxIDCancion(const unordered_map<int, Cancion>& canciones) {
    int maxID = 0;
    for (const auto& [id, c] : canciones)
        if (id > maxID) maxID = id;
    return maxID + 1;
}

int main() {
    unordered_map<int, Usuario> usuarios;
    unordered_map<int, Cancion> canciones;

    string archivo = "large.csv";

    Rendimiento medir;
    medir.iniciar();

    Reader::leerCSV(archivo, usuarios, canciones);

    medir.finalizar("Tiempo total de carga de datos");

    // Mostrar ranking de canciones
    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);
    cout << "\n- 5 canciones mas valoradas:\n";
    ranking.mostrarTop(5);

    // Sistema LSH
    int totalCanciones = obtenerMaxIDCancion(canciones);
    LSH sistemaLSH(5, totalCanciones, usuarios);
    sistemaRecomendaciones(sistemaLSH);

    return 0;
}
