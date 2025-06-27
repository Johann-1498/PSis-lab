#pragma once
#include "ExcepcionBase.h"

class ExcepcionBancaria : public ExcepcionBase {
protected:
    string codigoError;
    bool esRecuperable;
    string accionCorrectiva;

public:
    ExcepcionBancaria(string tipo, string mensaje, string codigoError,
                      bool esRecuperable, string accionCorrectiva,
                      Severidad severidad, int operacionID = -1)
        : ExcepcionBase(tipo, mensaje, severidad, operacionID),
          codigoError(codigoError), esRecuperable(esRecuperable),
          accionCorrectiva(accionCorrectiva) {}

    virtual string descripcion() const override {
        return ExcepcionBase::descripcion() +
               " [Código: " + codigoError + "] " +
               (esRecuperable ? "[Recuperable]" : "[No Recuperable]") +
               " Acción sugerida: " + accionCorrectiva;
    }
};
