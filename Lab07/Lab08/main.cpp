#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <cmath>

// Representa un usuario con sus canciones escuchadas
struct Usuario {
    std::unordered_set<int> canciones;
};

// LSH simple
class LSH {
public:
    int numHashes, numCanciones;
    std::vector<std::vector<double>> planos;
    std::unordered_map<int, std::vector<int>> buckets;
    std::unordered_map<int, Usuario> usuarios;

    LSH(int numHashes_, int numCanciones_)
        : numHashes(numHashes_), numCanciones(numCanciones_) {
        generarPlanosAleatorios();
    }

    void agregarUsuario(int id, const std::unordered_set<int>& canciones) {
        usuarios[id] = { canciones };
    }

    void construirBuckets() {
        for (const auto& [id, user] : usuarios) {
            int firma = calcularFirma(user);
            buckets[firma].push_back(id);
        }
    }

    void buscarSimilares(int id) {
        if (!usuarios.count(id)) {
            std::cout << "Usuario no encontrado.\n";
            return;
        }
        int firma = calcularFirma(usuarios[id]);
        auto& candidatos = buckets[firma];
        std::cout << "\nUsuarios similares a " << id << ":\n";
        for (int otro : candidatos) {
            if (otro == id) continue;
            int comunes = contarCancionesEnComun(usuarios[id], usuarios[otro]);
            if (comunes > 0) {
                std::cout << "- Usuario " << otro << " con " << comunes << " canciones en comun\n";
            }
        }
        if (candidatos.size() <= 1) {
            std::cout << "(No se encontraron usuarios con firmas similares)\n";
        }
    }

private:
    void generarPlanosAleatorios() {
        std::mt19937 gen(std::random_device{}());
        std::normal_distribution<double> dist(0.0, 1.0);
        planos.resize(numHashes, std::vector<double>(numCanciones));
        for (int i = 0; i < numHashes; ++i)
            for (int j = 0; j < numCanciones; ++j)
                planos[i][j] = dist(gen);
    }

    int calcularFirma(const Usuario& usuario) {
        int firma = 0;
        for (int i = 0; i < numHashes; ++i) {
            double suma = 0.0;
            for (int c : usuario.canciones)
                if (c < numCanciones)
                    suma += planos[i][c];
            if (suma > 0)
                firma |= (1 << i);
        }
        return firma;
    }

    int contarCancionesEnComun(const Usuario& u1, const Usuario& u2) {
        int count = 0;
        for (int c : u1.canciones)
            if (u2.canciones.count(c))
                ++count;
        return count;
    }
};

int main() {
    std::ifstream f("large.csv");
    if (!f) {
        std::cerr << "No se pudo abrir simple.csv\n";
        return 1;
    }

    std::unordered_map<int, std::unordered_set<int>> datos;
    int maxCancion = 0;
    std::string linea;
    while (std::getline(f, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        std::getline(ss, campo, ',');
        int usuarioID = std::stoi(campo);
        std::getline(ss, campo, ',');
        int cancionID = std::stoi(campo);
        datos[usuarioID].insert(cancionID);
        maxCancion = std::max(maxCancion, cancionID);
    }

    LSH lsh(5, maxCancion + 1);  // Reducido de 10 a 5 hashes
    for (const auto& [id, canciones] : datos)
        lsh.agregarUsuario(id, canciones);
    lsh.construirBuckets();

    while (true) {
        std::cout << "\nIngresa ID de usuario para buscar similares (-1 para salir): ";
        int id;
        std::cin >> id;
        if (id == -1) break;
        lsh.buscarSimilares(id);
    }

    return 0;
}
