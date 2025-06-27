// Excepciones.h
#pragma once
#include <stdexcept>
#include <string>

class ExcepcionesGenerales : public std::runtime_error {
public:
    explicit ExcepcionesGenerales(const std::string& mensaje)
      : std::runtime_error(mensaje) {}
};

class ExcepcionActivosNoValidos      : public ExcepcionesGenerales {
public: using ExcepcionesGenerales::ExcepcionesGenerales;

};
class ExcepcionLlegadaCorrecta      : public ExcepcionesGenerales {
public: using ExcepcionesGenerales::ExcepcionesGenerales;
};
class ExcepcionActualizacionDatos   : public ExcepcionesGenerales {
public: using ExcepcionesGenerales::ExcepcionesGenerales;
};
class ExcepcionDescargaActivos      : public ExcepcionesGenerales {
public: using ExcepcionesGenerales::ExcepcionesGenerales;
};
class ExcepcionCargadeArchivos      : public ExcepcionesGenerales {
public: using ExcepcionesGenerales::ExcepcionesGenerales;
};
