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

// LSH Multi-Probe para recomendaciones usuario-canción dispersas
// Similaridad mediante distancia euclidiana
// Número de tablas (numTablas) y de hashes por tabla (numHashes)
// se calcula dinámicamente según número de usuarios.

struct TablaLSH {
    int numHashes;       // cantidad de hiperpianos
    int dim;             // dimensión de vectores
    std::vector<std::vector<double>> planos; // numHashes x dim
    std::unordered_map<int, std::vector<int>> buckets; // idBucket -> lista de usuIDs

    // Inicializa numHashes planos aleatorios de dimensión dim
    TablaLSH(int numHashes_, int dim_, std::mt19937 &gen)
        : numHashes(numHashes_), dim(dim_) {
        std::normal_distribution<double> dist(0.0, 1.0);
        planos.resize(numHashes, std::vector<double>(dim));
        for(int i = 0; i < numHashes; ++i)
            for(int j = 0; j < dim; ++j)
                planos[i][j] = dist(gen);
    }

    // Calcula ID de bucket de un vector v usando signos de producto escalar
    int firma(const std::vector<double> &v) const {
        int id = 0;
        for(int i = 0; i < numHashes; ++i) {
            double producto = 0.0;
            for(int j = 0; j < dim; ++j)
                producto += planos[i][j] * v[j];
            if(producto > 0) id |= (1 << i);
        }
        return id;
    }
};

class LSHMultiProbe {
public:
    int numTablas, numHashes, dim;
    std::vector<TablaLSH*> tablas;

    // Crea índice LSH con parámetros según numUsuarios y dimensión
    LSHMultiProbe(int numUsuarios, int dimension)
        : dim(dimension) {
        calcularParam(numUsuarios, numTablas, numHashes);
        std::random_device rd;
        std::mt19937 gen(rd());
        tablas.reserve(numTablas);
        for(int t = 0; t < numTablas; ++t)
            tablas.push_back(new TablaLSH(numHashes, dim, gen));
    }

    ~LSHMultiProbe() {
        for(auto t : tablas) delete t;
    }

    // Inserta vector de usuario en todas las tablas
    void insertar(int usuID, const std::vector<double> &v) {
        for(auto t : tablas) {
            int idB = t->firma(v);
            t->buckets[idB].push_back(usuID);
        }
    }

    // Obtiene candidatos via multi-probe: bucket principal y vecinos
    void candidatos(const std::vector<double> &v,
                    std::unordered_set<int> &salida) const {
        std::vector<int> firmas(numTablas);
        for(int t = 0; t < numTablas; ++t)
            firmas[t] = tablas[t]->firma(v);

        for(int t = 0; t < numTablas; ++t) {
            auto &cub = tablas[t]->buckets;
            // bucket exacto
            auto it = cub.find(firmas[t]);
            if(it != cub.end())
                for(int u : it->second) salida.insert(u);
            // multi-probe: voltear cada bit
            for(int b = 0; b < numHashes; ++b) {
                int vecino = firmas[t] ^ (1 << b);
                auto it2 = cub.find(vecino);
                if(it2 != cub.end())
                    for(int u : it2->second) salida.insert(u);
            }
        }
    }

    // Distancia euclidiana entre dos vectores
    static double distEucl(const std::vector<double> &a,
                           const std::vector<double> &b) {
        double suma = 0.0;
        int n = a.size();
        for(int i = 0; i < n; ++i) {
            double d = a[i] - b[i];
            suma += d * d;
        }
        return std::sqrt(suma)/n;
    }

private:
    // Heurística: tablas = log2(N), hashes = max(1, tablas/2)
    static void calcularParam(int N, int &outT, int &outH) {
        int base = std::max(1, (int)std::round(std::log2(N)));
        outT = base;
        outH = std::max(1, base / 2);
    }
};

int main() {
    std::ifstream f("simple.csv");
    if(!f) { std::cerr << "No se puede abrir simple.csv\n"; return 1; }
    std::string linea;
    int maxCanc = 0;
    std::vector<std::tuple<int,int,double>> datos;

    // Leer CSV: usuID,cancID,calificacion
    while(std::getline(f, linea)) {
        std::istringstream ss(linea);
        int usu, can;
        double cal;
        if(!(ss >> usu)) continue;
        ss.ignore(); ss >> can;
        ss.ignore(); ss >> cal;
        datos.emplace_back(usu, can, cal);
        maxCanc = std::max(maxCanc, can);
    }

    // Vectorizar usuarios
    std::unordered_map<int, std::vector<double>> vecUsu;
    for(auto &r : datos) {
        int u, c; double v;
        std::tie(u,c,v) = r;
        if(!vecUsu.count(u))
            vecUsu[u] = std::vector<double>(maxCanc, 0.0);
        vecUsu[u][c-1] = v;
    }
    int nUsu = vecUsu.size();

    // Construir índice LSH
    LSHMultiProbe lsh(nUsu, maxCanc);
    for(auto &p : vecUsu)
        lsh.insertar(p.first, p.second);

    // Menú de consultas
    while(true) {
        std::cout << "Ingresa usuario (ID) para comparar (-1 sale): ";
        int consulta;
        std::cin >> consulta;
        if(consulta == -1) break;
        auto it = vecUsu.find(consulta);
        if(it == vecUsu.end()) {
            std::cout << "Usuario no existe.\n";
            continue;
        }
        // generar candidatos
        std::unordered_set<int> cand;
        lsh.candidatos(it->second, cand);
        // calcular distancias
        std::vector<std::pair<double,int>> lista;
        for(int u : cand) {
            if(u == consulta) continue;
            double d = LSHMultiProbe::distEucl(it->second, vecUsu[u]);
            lista.emplace_back(d,u);
        }
        std::sort(lista.begin(), lista.end());
        // mostrar top 5
        std::cout << "Top 5 similares a usuario " << consulta << ":\n";
        for(int i = 0; i < (int)lista.size() && i < 5; ++i)
            std::cout << "  " << lista[i].second
                      << " (dist=" << lista[i].first << ")\n";
    }
    std::cout << "Fin de consultas.\n";
    return 0;
}