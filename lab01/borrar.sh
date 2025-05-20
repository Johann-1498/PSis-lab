#!/bin/bash
archivo=$1
dir_temp="/tmp"
ruta_archivo_temp="$dir_temp/$(basename "$archivo")"

# Se realiza la copia
cp "$archivo" "$dir_temp"

# Se comprueba que la copia se realizó correctamente
if [ -f "$ruta_archivo_temp" ]; then
    echo "Archivo copiado correctamente en el directorio: $dir_temp"
    echo "Eliminando archivo"
    rm "$archivo"
else
    echo "Error: Archivo no copiado"
fi
