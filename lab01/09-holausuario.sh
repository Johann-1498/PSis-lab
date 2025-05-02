#!/bin/bash
if [ $# -lt 1 ]; then
    echo "Error: Proporcionar al menos un parametro."
    echo "Uso: $0 nombre1 [nombre2 ...]"
    echo "Ejemplo: $0 Ana Pedro Juan"
    exit 1
fi

for usuario in "$@"; do
    resultado=$(usuarioconectado "$usuario")
    if [ "$resultado" != "SI" ]; then
        echo "Error: El usuario '$usuario' no está conectado al sistema."
        exit 1
    fi
done

mensaje=$(printf "%s, " "$@")
mensaje=${mensaje%, } 

echo "Hola $mensaje!"
