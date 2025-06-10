#include "frases.h"

int main() {
    const std::string nombreArchivo = "frases.txt";

    escribirFrasesEnArchivo(nombreArchivo);
    mostrarContenidoDelArchivo(nombreArchivo);

    return 0;
}
