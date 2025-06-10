#ifndef USUARIO_H
#define USUARIO_H

#include <unordered_map>
#include <vector>
#include <algorithm>

// representacion dispersa de usuario - solo guarda las canciones que escucho
// esto ahorra mucha memoria porque no guarda ceros
struct Usuario {
    std::unordered_map<int, double> canciones; // cancionID -> calificacion
    std::vector<int> cancionesOrdenadas; // para hacer busquedas binarias rapidas
    
    // agrega una cancion con su calificacion al usuario
    void agregarCancion(int cancionID, double calificacion) {
        canciones[cancionID] = calificacion;
        cancionesOrdenadas.push_back(cancionID);
    }
    
    // ordena las canciones para poder hacer intersecciones eficientes
    void finalizarUsuario() {
        // ordenar para busquedas binarias eficientes
        std::sort(cancionesOrdenadas.begin(), cancionesOrdenadas.end());
    }
};

#endif