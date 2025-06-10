#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <cmath>
#include <limits>
#include <set>

// Representación dispersa de usuario: solo canciones escuchadas
struct UsuarioDisperso {
    std::unordered_map<int, double> canciones; // cancionID -> calificación
    std::vector<int> cancionesOrdenadas; // para iteración eficiente
    
    void agregarCancion(int cancionID, double calificacion) {
        canciones[cancionID] = calificacion;
        cancionesOrdenadas.push_back(cancionID);
    }
    
    void finalizarUsuario() {
        // Ordenar para búsquedas binarias eficientes
        std::sort(cancionesOrdenadas.begin(), cancionesOrdenadas.end());
    }
};

// LSH adaptado para vectores dispersos
struct TablaLSHDispersa {
    int numHashes;
    int numCancionesTotal;
    std::vector<std::vector<double>> planos; // numHashes x numCancionesTotal
    std::unordered_map<int, std::vector<int>> buckets;
    
    TablaLSHDispersa(int numHashes_, int numCancionesTotal_, std::mt19937 &gen)
        : numHashes(numHashes_), numCancionesTotal(numCancionesTotal_) {
        std::normal_distribution<double> dist(0.0, 1.0);
        planos.resize(numHashes, std::vector<double>(numCancionesTotal_));
        for(int i = 0; i < numHashes; ++i)
            for(int j = 0; j < numCancionesTotal_; ++j)
                planos[i][j] = dist(gen);
    }
    
    // Calcula firma LSH usando solo canciones que el usuario escuchó
    int firmaDispersa(const UsuarioDisperso &usuario) const {
        int id = 0;
        for(int i = 0; i < numHashes; ++i) {
            double producto = 0.0;
            // Solo considerar canciones que el usuario escuchó
            for(auto &par : usuario.canciones) {
                int cancionID = par.first;
                double calificacion = par.second;
                if(cancionID < numCancionesTotal) {
                    producto += planos[i][cancionID] * calificacion;
                }
            }
            if(producto > 0) id |= (1 << i);
        }
        return id;
    }
};

class LSHMultiProbeDisperso {
public:
    int numTablas, numHashes, numCancionesTotal;
    std::vector<TablaLSHDispersa*> tablas;
    std::unordered_map<int, UsuarioDisperso> usuarios;
    
    LSHMultiProbeDisperso(int numUsuarios, int numCancionesTotal_)
        : numCancionesTotal(numCancionesTotal_) {
        calcularParam(numUsuarios, numTablas, numHashes);
        std::random_device rd;
        std::mt19937 gen(rd());
        tablas.reserve(numTablas);
        for(int t = 0; t < numTablas; ++t)
            tablas.push_back(new TablaLSHDispersa(numHashes, numCancionesTotal, gen));
    }
    
    ~LSHMultiProbeDisperso() {
        for(auto t : tablas) delete t;
    }
    
    void agregarUsuario(int usuID, const std::vector<std::pair<int, double>>& cancionesCalifs) {
        UsuarioDisperso usuario;
        for(auto &par : cancionesCalifs) {
            usuario.agregarCancion(par.first, par.second);
        }
        usuario.finalizarUsuario();
        usuarios[usuID] = std::move(usuario);
    }
    
    void construirIndice() {
        for(auto &par : usuarios) {
            int usuID = par.first;
            UsuarioDisperso &usuario = par.second;
            
            for(auto t : tablas) {
                int idB = t->firmaDispersa(usuario);
                t->buckets[idB].push_back(usuID);
            }
        }
    }
    
    void candidatos(int usuarioConsulta, std::unordered_set<int> &salida) const {
        auto it = usuarios.find(usuarioConsulta);
        if(it == usuarios.end()) return;
        
        const UsuarioDisperso &usuario = it->second;
        
        std::vector<int> firmas(numTablas);
        for(int t = 0; t < numTablas; ++t)
            firmas[t] = tablas[t]->firmaDispersa(usuario);
        
        for(int t = 0; t < numTablas; ++t) {
            auto &cub = tablas[t]->buckets;
            
            // Bucket exacto
            auto it = cub.find(firmas[t]);
            if(it != cub.end())
                for(int u : it->second) salida.insert(u);
            
            // Multi-probe: voltear cada bit
            for(int b = 0; b < numHashes; ++b) {
                int vecino = firmas[t] ^ (1 << b);
                auto it2 = cub.find(vecino);
                if(it2 != cub.end())
                    for(int u : it2->second) salida.insert(u);
            }
        }
    }
    
    // Distancia euclidiana solo entre canciones compartidas
    double distanciaCancionesCompartidas(int usu1, int usu2) const {
        auto it1 = usuarios.find(usu1);
        auto it2 = usuarios.find(usu2);
        if(it1 == usuarios.end() || it2 == usuarios.end()) 
            return std::numeric_limits<double>::max();
        
        const UsuarioDisperso &u1 = it1->second;
        const UsuarioDisperso &u2 = it2->second;
        
        // Encontrar canciones compartidas usando iteradores ordenados
        std::vector<int> cancionesCompartidas;
        std::set_intersection(
            u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
            u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
            std::back_inserter(cancionesCompartidas)
        );
        
        if(cancionesCompartidas.empty()) {
            return std::numeric_limits<double>::max(); // Sin canciones en común
        }
        
        // Calcular distancia euclidiana solo en canciones compartidas
        double sumaDistancias = 0.0;
        for(int cancionID : cancionesCompartidas) {
            double cal1 = u1.canciones.at(cancionID);
            double cal2 = u2.canciones.at(cancionID);
            double diff = cal1 - cal2;
            sumaDistancias += diff * diff;
        }
        
        // Normalizar por número de canciones compartidas
        return std::sqrt(sumaDistancias) / cancionesCompartidas.size();
    }
    
    // Similitud de Pearson solo entre canciones compartidas
    double similitudPearsonCompartidas(int usu1, int usu2) const {
        auto it1 = usuarios.find(usu1);
        auto it2 = usuarios.find(usu2);
        if(it1 == usuarios.end() || it2 == usuarios.end()) 
            return -1.0;
        
        const UsuarioDisperso &u1 = it1->second;
        const UsuarioDisperso &u2 = it2->second;
        
        // Encontrar canciones compartidas
        std::vector<int> cancionesCompartidas;
        std::set_intersection(
            u1.cancionesOrdenadas.begin(), u1.cancionesOrdenadas.end(),
            u2.cancionesOrdenadas.begin(), u2.cancionesOrdenadas.end(),
            std::back_inserter(cancionesCompartidas)
        );
        
        if(cancionesCompartidas.size() < 2) {
            return -1.0; // Necesitamos al menos 2 canciones compartidas
        }
        
        // Calcular medias de calificaciones compartidas
        double suma1 = 0.0, suma2 = 0.0;
        for(int cancionID : cancionesCompartidas) {
            suma1 += u1.canciones.at(cancionID);
            suma2 += u2.canciones.at(cancionID);
        }
        double media1 = suma1 / cancionesCompartidas.size();
        double media2 = suma2 / cancionesCompartidas.size();
        
        // Calcular correlación de Pearson
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
    
    // Obtener estadísticas de un usuario
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
    static void calcularParam(int N, int &outT, int &outH) {
        int base = std::max(1, (int)std::round(std::log2(N)));
        outT = base;
        outH = std::max(1, base / 2);
    }
};

int main() {
    std::ifstream f("large.csv");
    if(!f) { 
        std::cerr << "No se puede abrir simple.csv\n"; 
        std::cerr << "Formato esperado: usuarioID,cancionID,calificacion\n";
        return 1; 
    }
    
    std::string linea;
    std::unordered_map<int, std::vector<std::pair<int, double>>> datosUsuarios;
    std::unordered_set<int> todasCanciones;
    int maxCancionID = 0;
    
    std::cout << "Cargando datos...\n";
    
    // Leer CSV y agrupar por usuario
    while(std::getline(f, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        
        // Leer usuarioID
        if(!std::getline(ss, campo, ',')) continue;
        int usuID = std::stoi(campo);
        
        // Leer cancionID
        if(!std::getline(ss, campo, ',')) continue;
        int cancionID = std::stoi(campo);
        
        // Leer calificación
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
    
    // Crear sistema LSH
    LSHMultiProbeDisperso lsh(datosUsuarios.size(), maxCancionID + 1);
    
    // Agregar usuarios al sistema
    std::cout << "Construyendo indice LSH...\n";
    for(auto &par : datosUsuarios) {
        lsh.agregarUsuario(par.first, par.second);
    }
    lsh.construirIndice();
    
    std::cout << "Sistema listo. Parametros LSH:\n";
    std::cout << "  Tablas: " << lsh.numTablas << "\n";
    std::cout << "  Hashes por tabla: " << lsh.numHashes << "\n";
    
    // Menú de consultas
    while(true) {
        std::cout << "\n=== MENÚ ===\n";
        std::cout << "1. Buscar usuarios similares\n";
        std::cout << "2. Ver estadisticas de usuario\n";
        std::cout << "3. Comparar dos usuarios especificos\n";
        std::cout << "4. Salir\n";
        std::cout << "Opcion: ";
        
        int opcion;
        std::cin >> opcion;
        
        if(opcion == 4) break;
        
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
                
                // Generar candidatos usando LSH
                std::unordered_set<int> candidatos;
                lsh.candidatos(consulta, candidatos);
                
                std::cout << "Candidatos encontrados: " << candidatos.size() << "\n";
                
                // Calcular similitudes usando ambas métricas
                std::vector<std::tuple<double, double, int>> resultados; // distancia, pearson, usuID
                
                for(int u : candidatos) {
                    if(u == consulta) continue;
                    
                    double distancia = lsh.distanciaCancionesCompartidas(consulta, u);
                    double pearson = lsh.similitudPearsonCompartidas(consulta, u);
                
                    if(distancia != std::numeric_limits<double>::max() && pearson != -1.0) {
                        resultados.emplace_back(distancia, pearson, u);
                    }
                }
                
                // Ordenar por distancia (menor = más similar)
                std::sort(resultados.begin(), resultados.end());
                
                std::cout << "\n4 usuarios similares a " << consulta << ":\n";
                std::cout << "Rank | Usuario | Distancia | Pearson | Canciones Compartidas\n";
                std::cout << "-----|---------|-----------|---------|---------------------\n";
                
                int count = 0;
                for(auto &resultado : resultados) {
                    if(count >= 4) break;
                    
                    double dist = std::get<0>(resultado);
                    double pearson = std::get<1>(resultado);
                    int usuID = std::get<2>(resultado);
                    
                    // Contar canciones compartidas
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
                    // Contar canciones compartidas
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
            
            default:
                std::cout << "Opcion invalida.\n";
        }
    }
    
    std::cout << "Fin del programa.\n";
    return 0;
}