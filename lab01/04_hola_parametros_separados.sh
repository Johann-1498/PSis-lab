#!/bin/bash
# 04_hola_parametros_separados.sh

if [ $# -lt 1 ]; then
    echo "Error: Proporciona al menos un parametro."
    exit 1
fi

mensaje=$(printf "%s, " "$@")
mensaje=${mensaje%, }

echo "Hola $mensaje!"
