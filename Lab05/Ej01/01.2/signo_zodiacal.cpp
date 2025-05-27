#include "signo_zodiacal.h"

static const SignoZodiacal signos[] = {
    {"Aries", 0.0, 29.99},
    {"Tauro", 30.0, 59.99},
    {"Geminis", 60.0, 89.99},
    {"Cancer", 90.0, 119.99},
    {"Leo", 120.0, 149.99},
    {"Virgo", 150.0, 179.99},
    {"Libra", 180.0, 209.99},
    {"Escorpio", 210.0, 239.99},
    {"Sagitario", 240.0, 269.99},
    {"Capricornio", 270.0, 299.99},
    {"Acuario", 300.0, 329.99},
    {"Piscis", 330.0, 359.99}
};

const SignoZodiacal* obtenerSignosTradicionales() {
    return signos;
}

int cantidadSignosTradicionales() {
    return sizeof(signos) / sizeof(SignoZodiacal);
}