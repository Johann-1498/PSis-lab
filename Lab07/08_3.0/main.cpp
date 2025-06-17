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
void mostrarRecomendacionesCanciones(LSH& agruparUsuarios, const unordered_map<int, Cancion>& canciones) {
    int usuarioID;
    cout << "\nIngrese ID de usuario para obtener recomendaciones (-1 para salir): ";
    cin >> usuarioID;

    while (usuarioID != -1) {
        vector<int> recomendaciones = agruparUsuarios.obtenerCancionesRecomendadas(usuarioID);
        
        if (recomendaciones.empty()) {
            cout << "No se encontraron recomendaciones " << usuarioID << endl;
        } else {
            cout << "\nCanciones recomendadas " << usuarioID << ":\n";
            for (int cancionID : recomendaciones) {
                if (canciones.count(cancionID)) {
                    const Cancion& c = canciones.at(cancionID);
                    cout << "- ID: " << c.id << " | Escuchas: " << c.cantidadEscuchas << " | Rating promedio: " << c.promedio() << endl;
                } else {
                    cout << "- ID: " << cancionID << " (información no disponible)\n";
                }
            }
        }
        
        cout << "\nIngrese otro ID de usuario (-1 para salir): ";
        cin >> usuarioID;
    }
}

void mostrarMenuRecomendaciones(LSH& agruparUsuarios, const unordered_map<int, Usuario>& usuarios, 
                              const unordered_map<int, Cancion>& canciones) {
    int opcion;
    
    while (true) {
        cout << "\n=== MENU DE RECOMENDACIONES ===";
        cout << "\n1. Buscar usuarios similares";
        cout << "\n2. Calcular distancia entre dos usuarios";
        cout << "\n3. Obtener recomendaciones de canciones";
        cout << "\n4. Salir";
        cout << "\nIngrese opcion: ";
        cin >> opcion;
        
        if (opcion == 4) break;
        
        switch(opcion) {
            case 1: {
                int consultaID;
                cout << "\nIngresa ID de usuario : ";
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
                cout << "\nIngrese ID del primer usuario: ";
                cin >> usuario1;
                cout << "Ingrese ID del segundo usuario: ";
                cin >> usuario2;
                
                try {
                    double distancia = agruparUsuarios.calcularDistanciaEntreUsuarios(usuario1, usuario2);
                    cout << "\nDistancia euclidiana entre " << usuario1 << " y  " << usuario2 
                         << ": " << distancia << endl;
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                mostrarRecomendacionesCanciones(agruparUsuarios, canciones);
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
    mostrarMenuRecomendaciones(agruparUsuarios, usuarios, canciones);

    return 0;
}