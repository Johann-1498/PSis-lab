#pragma once
#include "ExcepcionBancaria.h"

class ExcepcionAutenticacion : public ExcepcionBancaria {
    string metodo;
    string motivo;
    int intentos;

public:
    ExcepcionAutenticacion(string metodo, string motivo, int intentos, int operacionID = -1)
        : ExcepcionBancaria("ExcepcionAutenticacion",
                            "Fallo de autenticación",
                            "ERR_AUTH", true,
                            "Verifique credenciales o reintente más tarde.",
                            Severidad::CRITICA, operacionID),
          metodo(metodo), motivo(motivo), intentos(intentos) {}

    string descripcion() const override {
        ostringstream oss;
        oss << ExcepcionBancaria::descripcion()
            << " [Método: " << metodo << "] "
            << "[Motivo: " << motivo << "] "
            << "[Intentos fallidos: " << intentos << "]";
        return oss.str();
    }
};
