#!/bin/bash

if [ $# -eq 1 ]
then
    echo "Buscando el nombre de usuario: $1"
    #Se busca el nombre de usuario dentro del sistema 
    user=$1
    if grep "$user" /etc/passwd; then
        echo "SI"
    else
        echo "NO"
    fi
else
    echo "Error | Ingrese una sola palabra para buscar"
fi



