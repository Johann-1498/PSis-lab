#include <iostream>
#include <unordered_map>
#include "Reader.h"
#include "usuario.h"
#include "cancion.h"
#include "RankingCanciones.h"
#include "LSH.h"
#include "Rendimiento.h"

using namespace std;

void mostrarMenu(LSH& sistema, const unordered_map<int, Usuario>& usuarios, const unordered_map<int, Cancion>& canciones, RankingCanciones& ranking) {
    int opcion;
    do {
        cout << "\n=== MENU DE RECOMENDACIONES ===\n";
        cout << "1. Buscar usuarios similares\n";
        cout << "2. Calcular distancia entre dos usuarios\n";
        cout << "3. Obtener recomendaciones de canciones\n";
        cout << "4. Mostrar top N canciones\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id;
                cout << "- ID del usuario: ";
                cin >> id;
                sistema.buscarSimilares(id);
                break;
            }
            case 2: {
                int id1, id2;
                cout << "- ID usuario 1: ";
                cin >> id1;
                cout << "- ID usuario 2: ";
                cin >> id2;
                try {
                    double distancia = sistema.calcularDistanciaEntreUsuarios(id1, id2);
                    cout << "- Distancia euclidiana entre " << id1 << " y " << id2 << ": " << distancia << endl;
                } catch (const exception& e) {
                    cout << "- Error: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                int id;
                cout << "- ID del usuario para recomendaciones: ";
                cin >> id;
                vector<int> recomendaciones = sistema.obtenerCancionesRecomendadas(id);
                if (recomendaciones.empty()) {
                    cout << "- No se encontraron recomendaciones para ese usuario.\n";
                } else {
                    cout << "- Recomendaciones:\n";
                    for (int cancionID : recomendaciones) {
                        if (canciones.count(cancionID)) {
                            const Cancion& c = canciones.at(cancionID);
                            cout << "  - ID: " << c.id
                                 << " Escuchas: " << c.cantidadEscuchas
                                 << " Rating promedio: " << c.promedio() << endl;
                        } else {
                            cout << "  - ID: " << cancionID << " (sin informacion)\n";
                        }
                    }
                }
                break;
            }
            case 4: {
                int n;
                cout << "- Cantidad de canciones a mostrar: ";
                cin >> n;
                ranking.mostrarTop(n);
                break;
            }
            case 5:
                cout << "- Saliendo del sistema.\n";
                break;
            default:
                cout << "- Opcion no valida. Intenta otra vez.\n";
        }
    } while (opcion != 5);
}

int main() {
    unordered_map<int, Usuario> usuarios;
    unordered_map<int, Cancion> canciones;

    string archivo = "large.csv";

    Rendimiento medir;
    medir.iniciar();

    Reader::leerCSV(archivo, usuarios, canciones);

    medir.finalizar("Tiempo total de carga de datos");

    // Inicializar ranking de canciones
    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);
    cout << "\n- Top 5 canciones más valoradas:\n";
    ranking.mostrarTop(5);

    // Determinar el máximo ID de canción para LSH
    int totalCanciones = 0;
    for (const auto& [id, c] : canciones)
        totalCanciones = max(totalCanciones, id + 1);

    // Crear estructura LSH
    LSH sistema(5, totalCanciones, usuarios);

    // Mostrar menú
    mostrarMenu(sistema, usuarios, canciones, ranking);

    return 0;
}
