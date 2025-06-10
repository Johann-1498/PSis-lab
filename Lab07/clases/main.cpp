#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <cstdio>

// incluir todas las clases del sistema
#include "RankingCancion.h"
#include "UsuarioDisperso.h"
#include "TablaLSH.h"
#include "LSHMultiProbeDisperso.h"
#include "SistemaMetricas.h"

int main() {
    // crear sistema de metricas para medir rendimiento
    Metricas metricas;
    metricas.iniciarMedicion();
    
    std::ifstream f("large.csv");
    if(!f) { 
        std::cerr << "No se puede abrir large.csv\n"; 
        std::cerr << "Formato esperado: usuarioID,cancionID,calificacion\n";
        return 1; 
    }
    
    std::string linea;
    std::unordered_map<int, std::vector<std::pair<int, double>>> datosUsuarios;
    std::unordered_set<int> todasCanciones;
    int maxCancionID = 0;
    
    std::cout << "Cargando datos...\n";
    
    // leer csv y agrupar por usuario
    while(std::getline(f, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        
        // leer usuarioID
        if(!std::getline(ss, campo, ',')) continue;
        int usuID = std::stoi(campo);
        
        // leer cancionID
        if(!std::getline(ss, campo, ',')) continue;
        int cancionID = std::stoi(campo);
        
        // leer calificacion
        if(!std::getline(ss, campo, ',')) continue;
        double calificacion = std::stod(campo);
        
        datosUsuarios[usuID].emplace_back(cancionID, calificacion);
        todasCanciones.insert(cancionID);
        maxCancionID = std::max(maxCancionID, cancionID);
    }
    f.close();
    
    std::cout << "Datos cargados:\n";
    std::cout << "  Usuarios: " << datosUsuarios.size() << "\n";
    std::cout << "  Canciones unicas: " << todasCanciones.size() << "\n";
    std::cout << "  ID maximo de cancion: " << maxCancionID << "\n";
    
    // crear sistema lsh
    LSHMultiProbeDisperso lsh(datosUsuarios.size(), maxCancionID + 1);
    
    // agregar usuarios al sistema
    std::cout << "Construyendo indice LSH y rankings de canciones...\n";
    for(auto &par : datosUsuarios) {
        lsh.agregarUsuario(par.first, par.second);
    }
    lsh.construirIndice();
    
    std::cout << "Sistema listo. Parametros LSH:\n";
    std::cout << "  Tablas: " << lsh.numTablas << "\n";
    std::cout << "  Hashes por tabla: " << lsh.numHashes << "\n";
    
    // mostrar metricas iniciales
    metricas.mostrarMetricas();
    
    // menu de consultas
    while(true) {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. Buscar usuarios similares\n";
        std::cout << "2. Ver estadisticas de usuario\n";
        std::cout << "3. Comparar dos usuarios especificos\n";
        std::cout << "4. Top 5 usuarios que mejor rankean una cancion\n";
        std::cout << "5. Ver estadisticas completas de una cancion\n";
        std::cout << "6. Ver metricas del sistema\n";
        std::cout << "7. Salir\n";
        std::cout << "Opcion: ";
        
        int opcion;
        std::cin >> opcion;
        
        if(opcion == 7) break;
        
        switch(opcion) {
            case 1: {
                std::cout << "Ingresa ID de usuario: ";
                int consulta;
                std::cin >> consulta;
                
                auto itConsulta = lsh.usuarios.find(consulta);
                if(itConsulta == lsh.usuarios.end()) {
                    std::cout << "Usuario no existe.\n";
                    continue;
                }
                
                // generar candidatos usando lsh
                std::unordered_set<int> candidatos;
                lsh.candidatos(consulta, candidatos);
                
                std::cout << "Candidatos encontrados: " << candidatos.size() << "\n";
                
                // calcular similitudes usando ambas metricas
                std::vector<std::tuple<double, double, int>> resultados; // distancia, pearson, usuID
                
                for(int u : candidatos) {
                    if(u == consulta) continue;
                    
                    double distancia = lsh.distanciaCancionesCompartidas(consulta, u);
                    double pearson = lsh.similitudPearsonCompartidas(consulta, u);
                
                    if(distancia != std::numeric_limits<double>::max() && pearson != -1.0) {
                        resultados.emplace_back(distancia, pearson, u);
                    }
                }
                
                // ordenar por distancia (menor = mas similar)
                std::sort(resultados.begin(), resultados.end());
                
                // mostrar 10 usuarios similares (cambiado de 4 a 10)
                std::cout << "\n10 usuarios similares a " << consulta << ":\n";
                std::cout << "Rank | Usuario | Distancia | Pearson | Canciones Compartidas\n";
                std::cout << "-----|---------|-----------|---------|---------------------\n";
                
                int count = 0;
                for(auto &resultado : resultados) {
                    if(count >= 10) break; // cambiado de 4 a 10
                    
                    double dist = std::get<0>(resultado);
                    double pearson = std::get<1>(resultado);
                    int usuID = std::get<2>(resultado);
                    
                    // contar canciones compartidas
                    auto &u1 = lsh.usuarios.at(consulta);
                    auto &u2 = lsh.usuarios.at(usuID);
                    std::vector<int> compartidas;
                    std::set_intersection(
                        u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
                        u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
                        std::back_inserter(compartidas)
                    );
                    
                    printf("%4d | %7d | %9.4f | %7.3f | %19zu\n", 
                           count + 1, usuID, dist, pearson, compartidas.size());
                    count++;
                }
                
                if(count == 0) {
                    std::cout << "No se encontraron usuarios similares con canciones compartidas.\n";
                }
                break;
            }
            
            case 2: {
                std::cout << "Ingresa ID de usuario: ";
                int usuID;
                std::cin >> usuID;
                lsh.estadisticasUsuario(usuID);
                break;
            }
            
            case 3: {
                std::cout << "Ingresa ID del primer usuario: ";
                int usu1;
                std::cin >> usu1;
                
                std::cout << "Ingresa ID del segundo usuario: ";
                int usu2;
                std::cin >> usu2;
                
                double distancia = lsh.distanciaCancionesCompartidas(usu1, usu2);
                double pearson = lsh.similitudPearsonCompartidas(usu1, usu2);
                
                std::cout << "\nComparacion entre usuarios " << usu1 << " y " << usu2 << ":\n";
                
                if(distancia == std::numeric_limits<double>::max()) {
                    std::cout << "No tienen canciones en comun.\n";
                } else {
                    // contar canciones compartidas
                    auto &u1 = lsh.usuarios.at(usu1);
                    auto &u2 = lsh.usuarios.at(usu2);
                    std::vector<int> compartidas;
                    std::set_intersection(
                        u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
                        u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
                        std::back_inserter(compartidas)
                    );
                    
                    std::cout << "Canciones compartidas: " << compartidas.size() << "\n";
                    std::cout << "Distancia euclidiana: " << distancia << "\n";
                    std::cout << "Correlacion de Pearson: " << pearson << "\n";
                    
                    if(pearson > 0.7) std::cout << "-> Muy similares\n";
                    else if(pearson > 0.3) std::cout << "-> Moderadamente similares\n";
                    else if(pearson > 0.0) std::cout << "-> Poco similares\n";
                    else std::cout << "-> No similares o inversamente correlacionados\n";
                }
                break;
            }
            
            case 4: {
                std::cout << "Ingresa ID de cancion: ";
                int cancionID;
                std::cin >> cancionID;
                lsh.topRankingCancion(cancionID);
                break;
            }
            
            case 5: {
                std::cout << "Ingresa ID de cancion: ";
                int cancionID;
                std::cin >> cancionID;
                lsh.estadisticasCancion(cancionID);
                break;
            }
            
            case 6: {
                metricas.mostrarMetricas();
                break;
            }
            
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
    
    std::cout << "Fin del programa.\n";
    // mostrar metricas finales
    metricas.mostrarMetricas();
    return 0;
}