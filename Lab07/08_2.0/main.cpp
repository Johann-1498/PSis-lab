#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "RankingCanciones.h"
#include "LSH.h"

using namespace std;

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

        usuarios[usuarioID].id = usuarioID;
        usuarios[usuarioID].cancionesEscuchadas.insert(cancionID);

        canciones[cancionID].id = cancionID;
        canciones[cancionID].cantidadEscuchas++;
        canciones[cancionID].sumaCalificaciones += calificacion;
    }

    archivo.close();
}

int calcularTotalCanciones(const unordered_map<int, Cancion>& canciones) {
    int maxID = 0;
    for (const auto& [id, c] : canciones)
        if (id > maxID) maxID = id;
    return maxID + 1;
}

void mostrarMenuRecomendaciones(LSH& agruparUsuarios, const unordered_map<int, Usuario>& usuarios) {
    int opcion;
    
    while (true) {
        cout << "\n=== MENU DE RECOMENDACIONES ===";
        cout << "\n1. Buscar usuarios similares";
        cout << "\n2. Calcular distancia entre dos usuarios";
        cout << "\n3. Salir";
        cout << "\nIngrese opcion: ";
        cin >> opcion;
        
        if (opcion == 3) break;
        
        switch(opcion) {
            case 1: {
                int consultaID;
                cout << "\nIngresa ID de usuario: ";
                cin >> consultaID;
                
                if (!usuarios.count(consultaID)) {
                    cout << "Usuario no encontrado.\n";
                    break;
                }
                
                agruparUsuarios.buscarSimilares(consultaID);
                break;
            }
            case 2: {
                int usuario1, usuario2;
                cout << "\nIngrese primer ID:";
                cin >> usuario1;
                cout << "Ingrese segudno ID:";
                cin >> usuario2;
                
                try {
                    double distancia = agruparUsuarios.calcularDistanciaEntreUsuarios(usuario1, usuario2);
                    cout << "\nDistancia entre usuario " << usuario1 << " y usuario " << usuario2 
                         << ": " << distancia << endl;
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            default:
                cout << "Opcion no valida.\n";
        }
    }
}

int main() {
    unordered_map<int, Usuario> usuarios;
    unordered_map<int, Cancion> canciones;

    // Paso 1: Cargar el archivo CSV
    string archivo = "large.csv";
    procesarArchivoCSV(archivo, usuarios, canciones);

    // Paso 2: Mostrar el ranking de canciones
    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);
    cout << "\nCanciones mas valoradas:\n";
    ranking.mostrarTop(5);

    // Paso 3: Construir LSH y ejecutar recomendaciones
    int totalCanciones = calcularTotalCanciones(canciones);
    LSH agruparUsuarios(5, totalCanciones, usuarios);
    mostrarMenuRecomendaciones(agruparUsuarios, usuarios);

    return 0;
}