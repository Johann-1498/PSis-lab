// --- Archivo: main.cpp ---
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "Usuario.h"
#include "Cancion.h"
#include "Registro.h"
#include "Reader.h"
#include "RankingCanciones.h"
#include "LSH.h"
#include "Rendimiento.h"

using namespace std;

void mostrarMenu(LSH& sistema,
                 const unordered_map<int, Usuario>& usuarios,
                 const unordered_map<int, Cancion>& canciones,
                 RankingCanciones& ranking);

int main() {
    unordered_map<int, Usuario> usuarios;
    unordered_map<int, Cancion> canciones;
    const string archivo = "ratings_big.csv";

    usuarios.reserve(162541 * 1.1);
    canciones.reserve(59047 * 1.1);


    Rendimiento medir;
    medir.iniciar();

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) {
        // --- Proceso HIJO ---
        close(fd[0]);
        Reader::leerCSVConHilos(archivo, fd[1]);
        _exit(EXIT_SUCCESS);
    }

    // --- Proceso PADRE ---
    close(fd[1]);
    Registro reg;
    // --- CORRECCIÓN AQUÍ ---
    while (read(fd[0], &reg, sizeof(reg)) == sizeof(reg)) {
        usuarios[reg.usuarioID].id = reg.usuarioID;
        usuarios[reg.usuarioID].cancionesEscuchadas.insert(reg.cancionID);
        canciones[reg.cancionID].id = reg.cancionID;
        canciones[reg.cancionID].cantidadEscuchas++;
        canciones[reg.cancionID].sumaCalificaciones += reg.calif;
    }
    close(fd[0]);

    int status;
    waitpid(pid, &status, 0);
    medir.finalizar("[Padre] Tiempo total de carga de datos (via pipe)");

    cout << "[Padre] Datos recibidos: " << usuarios.size() << " usuarios y " << canciones.size() << " canciones.\n";
    cout << "[Padre] Iniciando construcción de estructuras...\n";

    Rendimiento medirEstructuras;
    medirEstructuras.iniciar();

    RankingCanciones ranking;
    ranking.insertarCanciones(canciones);
    
    int totalCanciones = 0;
    if (!canciones.empty()) {
        for (const auto& [id, c] : canciones) {
            totalCanciones = max(totalCanciones, id + 1);
        }
    }
    
    LSH sistema(6, totalCanciones, usuarios);
    
    medirEstructuras.finalizar("Tiempo de construcción de Heap y LSH");

    cout << "\n- Top 5 canciones más valoradas:\n";
    ranking.mostrarTop(5);
    
    mostrarMenu(sistema, usuarios, canciones, ranking);

    return 0;
}

void mostrarMenu(LSH& sistema,
                 const unordered_map<int, Usuario>& usuarios,
                 const unordered_map<int, Cancion>& canciones,
                 RankingCanciones& ranking) {
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
                    cerr << "- Error: " << e.what() << endl;
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
                                 << " (Rating: " << c.promedio() << ")" << endl;
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