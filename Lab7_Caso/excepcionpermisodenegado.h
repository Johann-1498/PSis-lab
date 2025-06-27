#pragma once
#include "ExcepcionArchivoCSV.h"

class ExcepcionArchivoNoEncontrado : public ExcepcionArchivoCSV {
public:
    ExcepcionArchivoNoEncontrado(const string& ruta, int operacionID = -1)
        : ExcepcionArchivoCSV("ExcepcionArchivoNoEncontrado",
                               "No se encontró el archivo especificado",
                               ruta, "ERR_CSV_001", false,
                               "Verifique la ruta o cree el archivo si no existe.",
                               Severidad::ALTA, operacionID) {}
};
