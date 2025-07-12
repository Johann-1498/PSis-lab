// ExcepcionEscrituraFallidaCSV.h
#pragma once
#include "ExcepcionArchivoCSV.h"

class ExcepcionEscrituraFallidaCSV : public ExcepcionArchivoCSV {
public:
    ExcepcionEscrituraFallidaCSV(const std::string& ruta, int operacionID = -1)
        : ExcepcionArchivoCSV("ExcepcionEscrituraFallidaCSV",
                            "Falló la escritura en el archivo CSV",
                            ruta, "ERR_CSV_004", false,
                            "Verifique que el archivo no esté bloqueado por otro proceso.",
                            Severidad::ALTA, operacionID) {}
};