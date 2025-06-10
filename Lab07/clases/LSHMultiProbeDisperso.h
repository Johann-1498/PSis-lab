#ifndef LSH_MULTIPROBE_DISPERSO_H
#define LSH_MULTIPROBE_DISPERSO_H

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
#include "RankingCancion.h"
#include "UsuarioDisperso.h"
#include "TablaLSH.h"

class LSHMultiProbeDisperso {
public:
    int numTablas, numHashes, numCancionesTotal;
    std::vector<TablaLSHDispersa*> tablas;
    std::unordered_map<int, UsuarioDisperso> usuarios;
    // estructura para ranking de canciones: cancionID -> priority_queue
    std::unordered_map<int, std::priority_queue<RankingCancion>> rankingsPorCancion;
    
    // constructor que calcula parametros automaticamente segun numero de usuarios
    LSHMultiProbeDisperso(int numUsuarios, int numCancionesTotal_)
        : numCancionesTotal(numCancionesTotal_) {
        calcularParam(numUsuarios, numTablas, numHashes);
        std::random_device rd;
        std::mt19937 gen(rd());
        tablas.reserve(numTablas);
        // crear todas las tablas lsh
        for(int t = 0; t < numTablas; ++t)
            tablas.push_back(new TablaLSHDispersa(numHashes, numCancionesTotal, gen));
    }
    
    // destructor para liberar memoria de las tablas
    ~LSHMultiProbeDisperso() {
        for(auto t : tablas) delete t;
    }
    
    // agrega un usuario al sistema con sus canciones y calificaciones
    void agregarUsuario(int usuID, const std::vector<std::pair<int, double>>& cancionesCalifs) {
        UsuarioDisperso usuario;
        int ordenDescubrimiento = 0;
        
        for(auto &par : cancionesCalifs) {
            int cancionID = par.first;
            double calificacion = par.second;
            
            usuario.agregarCancion(cancionID, calificacion);
            
            // agregar al ranking de la cancion
            rankingsPorCancion[cancionID].push(RankingCancion(usuID, calificacion, ordenDescubrimiento++));
        }
        usuario.finalizarUsuario();
        usuarios[usuID] = std::move(usuario);
    }
    
    // construye el indice lsh - debe llamarse despues de agregar todos los usuarios
    void construirIndice() {
        for(auto &par : usuarios) {
            int usuID = par.first;
            UsuarioDisperso &usuario = par.second;
            
            // agregar usuario a todas las tablas lsh
            for(auto t : tablas) {
                int idB = t->firmaDispersa(usuario);
                t->buckets[idB].push_back(usuID);
            }
        }
    }
    
    // encuentra candidatos similares usando lsh + multiprobe
    void candidatos(int usuarioConsulta, std::unordered_set<int> &salida) const {
        auto it = usuarios.find(usuarioConsulta);
        if(it == usuarios.end()) return;
        
        const UsuarioDisperso &usuario = it->second;
        
        // calcular firmas para todas las tablas
        std::vector<int> firmas(numTablas);
        for(int t = 0; t < numTablas; ++t)
            firmas[t] = tablas[t]->firmaDispersa(usuario);
        
        for(int t = 0; t < numTablas; ++t) {
            auto &cub = tablas[t]->buckets;
            
            // bucket exacto
            auto it = cub.find(firmas[t]);
            if(it != cub.end())
                for(int u : it->second) salida.insert(u);
            
            // multiprobe: voltear cada bit para encontrar vecinos cercanos
            for(int b = 0; b < numHashes; ++b) {
                int vecino = firmas[t] ^ (1 << b);
                auto it2 = cub.find(vecino);
                if(it2 != cub.end())
                    for(int u : it2->second) salida.insert(u);
            }
        }
    }
    
    // calcula distancia euclidiana solo entre canciones que ambos usuarios escucharon
    double distanciaCancionesCompartidas(int usu1, int usu2) const {
        auto it1 = usuarios.find(usu1);
        auto it2 = usuarios.find(usu2);
        if(it1 == usuarios.end() || it2 == usuarios.end()) 
            return std::numeric_limits<double>::max();
        
        const UsuarioDisperso &u1 = it1->second;
        const UsuarioDisperso &u2 = it2->second;
        
        // encontrar canciones compartidas usando interseccion de conjuntos ordenados
        std::vector<int> cancionesCompartidas;
        std::set_intersection(
            u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
            u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
            std::back_inserter(cancionesCompartidas)
        );
        
        if(cancionesCompartidas.empty()) {
            return std::numeric_limits<double>::max(); // sin canciones en comun
        }
        
        // calcular distancia euclidiana solo en canciones compartidas
        double sumaDistancias = 0.0;
        for(int cancionID : cancionesCompartidas) {
            double cal1 = u1.canciones.at(cancionID);
            double cal2 = u2.canciones.at(cancionID);
            double diff = cal1 - cal2;
            sumaDistancias += diff * diff;
        }
        
        // normalizar por numero de canciones compartidas
        return std::sqrt(sumaDistancias) / cancionesCompartidas.size();
    }
    
    // calcula correlacion de pearson solo entre canciones compartidas
    double similitudPearsonCompartidas(int usu1, int usu2) const {
        auto it1 = usuarios.find(usu1);
        auto it2 = usuarios.find(usu2);
        if(it1 == usuarios.end() || it2 == usuarios.end()) 
            return -1.0;
        
        const UsuarioDisperso &u1 = it1->second;
        const UsuarioDisperso &u2 = it2->second;
        
        // encontrar canciones compartidas
        std::vector<int> cancionesCompartidas;
        std::set_intersection(
            u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
            u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
            std::back_inserter(cancionesCompartidas)
        );
        
        if(cancionesCompartidas.size() < 2) {
            return -1.0; // necesitamos al menos 2 canciones compartidas
        }
        
        // calcular medias de calificaciones compartidas
        double suma1 = 0.0, suma2 = 0.0;
        for(int cancionID : cancionesCompartidas) {
            suma1 += u1.canciones.at(cancionID);
            suma2 += u2.canciones.at(cancionID);
        }
        double media1 = suma1 / cancionesCompartidas.size();
        double media2 = suma2 / cancionesCompartidas.size();
        
        // calcular correlacion de pearson
        double numerador = 0.0;
        double sumaCuad1 = 0.0, sumaCuad2 = 0.0;
        
        for(int cancionID : cancionesCompartidas) {
            double cal1 = u1.canciones.at(cancionID);
            double cal2 = u2.canciones.at(cancionID);
            double diff1 = cal1 - media1;
            double diff2 = cal2 - media2;
            
            numerador += diff1 * diff2;
            sumaCuad1 += diff1 * diff1;
            sumaCuad2 += diff2 * diff2;
        }
        
        double denominador = std::sqrt(sumaCuad1 * sumaCuad2);
        if(denominador == 0.0) return 0.0;
        
        return numerador / denominador;
    }
    
    // obtiene top 5 usuarios que mejor rankean una cancion
    void topRankingCancion(int cancionID) const {
        auto it = rankingsPorCancion.find(cancionID);
        if(it == rankingsPorCancion.end()) {
            std::cout << "Cancion " << cancionID << " no encontrada en el sistema.\n";
            return;
        }
        
        // hacer una copia del heap para no modificar el original
        std::priority_queue<RankingCancion> heapCopia = it->second;
        
        std::cout << "\nTop 5 usuarios que mejor rankean la cancion " << cancionID << ":\n";
        std::cout << "Rank | Usuario | Calificacion\n";
        std::cout << "-----|---------|-------------\n";
        
        int rank = 1;
        while(!heapCopia.empty() && rank <= 5) {
            RankingCancion top = heapCopia.top();
            heapCopia.pop();
            
            std::cout << std::setw(4) << rank << " | " 
                      << std::setw(7) << top.usuarioID << " | " 
                      << std::setw(11) << std::fixed << std::setprecision(3) << top.calificacion << "\n";
            rank++;
        }
        
        if(rank == 1) {
            std::cout << "No hay usuarios que hayan rankeado esta cancion.\n";
        }
    }
    
    // obtiene estadisticas basicas de una cancion (sin desviacion ni rango)
    void estadisticasCancion(int cancionID) const {
        auto it = rankingsPorCancion.find(cancionID);
        if(it == rankingsPorCancion.end()) {
            std::cout << "Cancion " << cancionID << " no encontrada en el sistema.\n";
            return;
        }
        
        // hacer una copia del heap para calcular estadisticas
        std::priority_queue<RankingCancion> heapCopia = it->second;
        std::vector<double> calificaciones;
        
        while(!heapCopia.empty()) {
            calificaciones.push_back(heapCopia.top().calificacion);
            heapCopia.pop();
        }
        
        if(calificaciones.empty()) {
            std::cout << "No hay calificaciones para la cancion " << cancionID << ".\n";
            return;
        }
        
        // calcular promedio
        double suma = 0.0;
        for(double cal : calificaciones) {
            suma += cal;
        }
        double promedio = suma / calificaciones.size();
        
        std::cout << "\nEstadisticas de la cancion " << cancionID << ":\n";
        std::cout << "  Total de calificaciones: " << calificaciones.size() << "\n";
        std::cout << "  Calificacion promedio: " << std::fixed << std::setprecision(3) << promedio << "\n";
    }
    
    // obtiene estadisticas de un usuario
    void estadisticasUsuario(int usuID) const {
        auto it = usuarios.find(usuID);
        if(it == usuarios.end()) {
            std::cout << "Usuario " << usuID << " no existe.\n";
            return;
        }
        
        const UsuarioDisperso &usuario = it->second;
        std::cout << "Usuario " << usuID << ":\n";
        std::cout << "  Canciones escuchadas: " << usuario.canciones.size() << "\n";
        
        if(!usuario.canciones.empty()) {
            double suma = 0.0;
            double minCal = std::numeric_limits<double>::max();
            double maxCal = std::numeric_limits<double>::lowest();
            
            for(auto &par : usuario.canciones) {
                double cal = par.second;
                suma += cal;
                minCal = std::min(minCal, cal);
                maxCal = std::max(maxCal, cal);
            }
            
            double promedio = suma / usuario.canciones.size();
            std::cout << "  Calificacion promedio: " << promedio << "\n";
            std::cout << "  Rango de calificaciones: [" << minCal << ", " << maxCal << "]\n";
        }
    }

private:
    // calcula parametros optimos de lsh segun numero de usuarios
    static void calcularParam(int N, int &outT, int &outH) {
        int base = std::max(1, (int)std::round(std::log2(N)));
        outT = base;
        outH = std::max(1, base / 2);
    }
};

#endif