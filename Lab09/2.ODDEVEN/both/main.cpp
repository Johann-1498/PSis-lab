#include "oddtrace.h"

int main(int argc, char* argv[]) {
    // Código principal aquí
    int n, num_procs, num_threads;
    char g_i;
    int* a;

    Get_args(argc, argv, &n, &g_i, &num_procs, &num_threads);
    
    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    if (g_i == 'g') {
        Generate_list(a, n);
        Print_list(a, n, "Lista original");
    } else {
        Read_list(a, n);
    }

    Odd_even_sort(a, n, num_procs, num_threads);

    Print_list(a, n, "Lista ordenada");
    
    free(a);
    return EXIT_SUCCESS;
}
