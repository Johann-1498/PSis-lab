#pragma once
#include "ExcepcionBancaria.h"

class ExcepcionArchivoCSV : public ExcepcionBancaria {
protected:
    string rutaArchivo;
public:
    ExcepcionArchivoCSV(const string& tipo, const string& mensaje,
                        const string& ruta, const string& codigoError,
                        bool esRecuperable, const string& accion,
                        Severidad severidad, int operacionID = -1)
        : ExcepcionBancaria(tipo, mensaje, codigoError, esRecuperable, accion, severidad, operacionID),
          rutaArchivo(ruta) {}

    string descripcion() const override {
        return ExcepcionBancaria::descripcion() + " [Archivo: " + rutaArchivo + "]";
    }
};
