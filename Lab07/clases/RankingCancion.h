#ifndef RANKING_CANCION_H
#define RANKING_CANCION_H

// estructura que guarda el ranking de cada usuario para una cancion
struct RankingCancion {
    int usuarioID;
    double calificacion;
    int ordenDescubrimiento; // para cuando hay empates, el primero que se encontro gana
    
    RankingCancion(int uID, double cal, int orden) 
        : usuarioID(uID), calificacion(cal), ordenDescubrimiento(orden) {}
    
    // comparador para el max heap - queremos las mejores calificaciones arriba
    bool operator<(const RankingCancion& other) const {
        if (calificacion != other.calificacion) {
            return calificacion < other.calificacion; // max heap por calificacion
        }
        // si empatan, el que fue encontrado primero tiene prioridad
        return ordenDescubrimiento > other.ordenDescubrimiento;
    }
};

#endif