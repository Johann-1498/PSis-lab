#pragma once

#include <unordered_map>
#include "Activos.h" // Necesario para la definición de CodigoActivo

// Define el tipo estándar para una solicitud de activos,
// que mapea un código de activo a un monto o cantidad.
using SolicitudActivos = std::unordered_map<CodigoActivo, double>;