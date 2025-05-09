#!/bin/bash

rutaActual=$(pwd)

# Verificar si se pasó un nombre como argumento
if [ $# -lt 1 ]; then
	echo "Error: Proporcionar al menos un parámetro."
	exit 1
fi

nombre="$1"
rutaBuscar="$rutaActual/$nombre"

# Verifica si el archivo o directorio existe
if test -e "$rutaBuscar"; then

	# Si es archivo
	if test -f "$rutaBuscar"; then
    	echo "'$nombre' es un archivo"

	# Si es directorio
	elif test -d "$rutaBuscar"; then
    	nElementos=$(ls -A "$rutaBuscar" | wc -l)
    	echo "'$nombre' es un directorio y contiene $nElementos elementos incluyendo los ocultos"

	# Si no es archivo ni directorio
	else
    	echo "'$nombre' no es un archivo ni un directorio"
	fi

else
	echo "El elemento '$nombre' no existe en la ruta $rutaActual"
fi
