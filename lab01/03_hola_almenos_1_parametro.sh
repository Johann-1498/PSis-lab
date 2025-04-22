#!/bin/bash
# 03_hola_almenos_1_parametro.sh

if [ $# -lt 1 ]; then
    echo "Error: Proporcionar al menos un parámetro."
    exit 1
fi

echo "Hola $@!"
