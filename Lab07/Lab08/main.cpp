#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "RankingCanciones.h"
#include "LSH.h"

using namespace std;

// Función que carga datos desde el CSV y actualiza estructuras
void procesarArchivoCSV(const string& rutaCSV, unordered_map<int, Usuario>& usuarios, unordered_map<int, Cancion>& canciones) {
    ifstream archivo(rutaCSV);
    if (!archivo.is_open()) {
        cerr << "Error, no se puede acceder al archivo" << rutaCSV << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        int usuarioID, cancionID;
        double calificacion;

        getline(ss, campo, ',');
        usuarioID = stoi(campo);
        getline(ss, campo, ',');
        cancionID = stoi(campo);
        getline(ss, campo, ',');
        calificacion = stod(campo);

        // Registrar canción en usuario
        usuarios[usuarioID].id = usuarioID;
        usuarios[usuarioID].cancionesEscuchadas.insert(cancionID);

        // Registrar info en Cancion
        canciones[cancionID].id = cancionID;
        canciones[cancionID].cantidadEscuchas++;
        canciones[cancionID].sumaCalificaciones += calificacion;
    }

    archivo.close();
}

// Calcular el ID máximo de canciones para definir espacio en LSH
int calcularTotalCanciones(const unordered_map<int, Cancion>& canciones) {
    int maxID = 0;
    for (const auto& [id, c] : canciones)
        if (id > maxID) maxID = id;
    return maxID + 1;
}

// Ejecuta búsqueda de similares por LSH
void sistemaRecomendaciones(LSH& agruparUsuarios) {
    int consultaID;
    cout << "\n👤 Ingresa ID de usuario para buscar similares (-1 para salir): ";
    cin >> consultaID;

    while (consultaID != -1) {
        agruparUsuarios.buscarSimilares(consultaID);
        cout << "\n👤 Ingresa otro ID (-1 para salir): ";
        cin >> consultaID;
    }
}

int main() {
    unordered_map<int, Usuario> usuarios;
    unordered_map<int, Cancion> canciones;

    // Paso 1: Cargar el archivo CSV
    string archivo = "large.csv";  // Asegúrate que esté en la misma carpeta
    procesarArchivoCSV(archivo, usuarios, canciones);

    // Paso 2: Mostrar el ranking de canciones
    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);
    cout << "\n🎶 Canciones mas valoradas:\n";
    ranking.mostrarTop(5);

    // Paso 3: Construir LSH y ejecutar recomendaciones
    int totalCanciones = calcularTotalCanciones(canciones);
    LSH agruparUsuarios(5, totalCanciones, usuarios);
    sistemaRecomendaciones(agruparUsuarios);

    return 0;
}
