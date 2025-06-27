#pragma once
#include "Excepciones.h"

/// Fachada única para despachar y manejar errores
class GestorExcepciones {
public:
    static void manejar(const ExcepcionesGenerales& e);
};
