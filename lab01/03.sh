#!/bin/bash
if [ $# -lt 1 ]; then
    echo "Error: Proporcionar al menos un parámetro."
    exit 1
fi
echo "Hola $@!"