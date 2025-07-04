#pragma once
#include "TipoOperacion.h"
#include "SolicitudActivos.h"
#include "RegistroExceptions.h"
#include "String"

// Forward declarations
class Boveda;
class Transportador;

class Registro {
    public:
        const String dia;
        const String mes;
        const SolicitudActivos solicitud;
        Boveda* const boveda_afectada;
        Transportador* const transportador;
        const double monto_total;


        Registro(const SolicitudActivos& sol, Boveda* boveda, Transportador* trans)//Solicitud y bveda estan en la paradaRuta(DENTRO DE PLAZA)
        :   dia(sol.dia),
            mes(sol.mes),
            solicitud(sol),
            boveda_afectada(boveda),
            transportador(trans),
            monto_total(calculateTotal(sol))

        { validateInput(sol);}

    private:
        void validateInput(const SolicitudActivos& sol) const {//corregir
            sol.validar();
        }
        
        bool equals(const Registro& otro) const{//MEJORAR CORREGIR
            if (tipo != otro.tipo) return false;
            if (this.monto_total - otro.monto_total != 0) return false;
            if ((transportador == nullptr) != (otro.transportador == nullptr)) return false;
            if ( transportador->getNombre() != otro.transportador->getNombre()) return false;
            return true;

        }

        double calculateTotal(const SolicitudActivos& sol) const {
            double total = 0.0;
            for (const auto& item : sol.activos) {
                total += item.second;
            }
            
            if (total <= 0) {
                throw RegistroMontoInvalidoException(total);
            }
            return total;
        }
};