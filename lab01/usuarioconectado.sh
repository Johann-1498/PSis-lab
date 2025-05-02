#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Uso: $0 nombre_usuario"
    exit 1
fi

if who | grep -q "^$1 "; then
    echo "SI"
else
    echo "NO"
fi
