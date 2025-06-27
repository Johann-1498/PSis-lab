#pragma once
#include <string>
#include <ctime>
#include <sstream>
#include <exception>

using namespace std;

enum class Severidad { BAJA, MEDIA, ALTA, CRITICA };

class ExcepcionBase : public exception {
protected:
    string tipo;
    string mensaje;
    time_t fechaHora;
    Severidad severidad;
    string stackTrace;
    int operacionID;

public:
    ExcepcionBase(string tipo, string mensaje, Severidad severidad, int operacionID = -1)
        : tipo(tipo), mensaje(mensaje), severidad(severidad), operacionID(operacionID) {
        fechaHora = time(nullptr);
    }

    const char* what() const noexcept override {
        return mensaje.c_str();
    }

    virtual string descripcion() const {
        ostringstream oss;
        oss << "[Tipo: " << tipo << "] "
            << "[Severidad: " << severidadToStr(severidad) << "] "
            << "[Mensaje: " << mensaje << "]";
        return oss.str();
    }

    static string severidadToStr(Severidad s) {
        switch (s) {
            case Severidad::BAJA: return "BAJA";
            case Severidad::MEDIA: return "MEDIA";
            case Severidad::ALTA: return "ALTA";
            case Severidad::CRITICA: return "CRITICA";
        }
        return "DESCONOCIDA";
    }

    virtual ~ExcepcionBase() = default;
};
