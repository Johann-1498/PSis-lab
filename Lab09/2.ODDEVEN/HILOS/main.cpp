#include <stdio.h>
#include <stdlib.h>
#include "oddtrace.h"

int main(int argc, char* argv[]) {
    int n;
    char g_i;
    int* a;

    // Obtener argumentos
    Get_args(argc, argv, &n, &g_i);
    
    // Reservar memoria
    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(1);
    }

    // Generar o leer lista
    if (g_i == 'g') {
        Generate_list(a, n);
        print(a, n, "Lista original");
    } else {
        Read_list(a, n);
    }

    // Ordenar lista
    Odd_even_sort(a, n);

    // Mostrar resultado final
    print(a, n, "Lista ordenada");
    
    // Liberar memoria
    free(a);
    return 0;
}
