#pragma once

// Struct para enviar (usuarioID, cancionID, calif) por pipe
struct Registro {
    int usuarioID;
    int cancionID;
    double calif;
};
