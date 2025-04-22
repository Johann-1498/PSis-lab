#!/bin/bash
# 05_hola_con_ayuda.sh

if [ $# -lt 1 ]; then
    echo "Error: Proporcionar al menos un parametro."
    echo "Uso: $0 nombre1 [nombre2 ...]"
    echo "Ejemplo: $0 Ana Pedro Juan"
    exit 1
fi

mensaje=$(printf "%s, " "$@")
mensaje=${mensaje%, }  # Quitar la última coma y espacio

echo "Hola $mensaje!"
