#include "oddTrace.h"
#include <iostream>

void Usage(const char* prog_name) {
    fprintf(stderr, "uso:   %s <n> <g|i>\n", prog_name);
    fprintf(stderr, "   n:   numero de elementos en la lista\n");
    fprintf(stderr, "  'g':  generar lista aleatoria\n");
    fprintf(stderr, "  'i':  ingresar lista manualmente\n");
}

void Get_args(int argc, char* argv[], int* n_p, char* g_i_p) {
    if (argc != 3) {
        Usage(argv[0]);
        exit(0);
    }
    
    *n_p = atoi(argv[1]);
    *g_i_p = argv[2][0];
 
    if (*n_p <= 0 || (*g_i_p != 'g' && *g_i_p != 'i')) {
        Usage(argv[0]);
        exit(0);
    }
}

void Generate_list(int a[], int n) {
    srand(0);
    for (int i = 0; i < n; i++)
        a[i] = rand() % RMAX;
}

void Print_list(int a[], int n, const char* title) {
    printf("%s:\n", title);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n\n");
}

void Read_list(int a[], int n) {
    printf("Ingrese %d elementos:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void Compare_and_swap(int* a, int i, int j) {
    if (a[i] > a[j]) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

void Odd_even_sort(int a[], int n) {
    // Crear memoria compartida
    int* shared_arr = (int*)mmap(NULL, n * sizeof(int),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    // Copiar datos a memoria compartida
    for (int i = 0; i < n; i++) {
        shared_arr[i] = a[i];
    }

    for (int phase = 0; phase < n; phase++) {
        printf("Fase %d (%s):\n", phase, (phase % 2 == 0) ? "par" : "impar");
        
        if (phase % 2 == 0) { // Fase par
            for (int i = 1; i < n; i += 2) {
                pid_t pid = fork();
                if (pid == 0) { // Proceso hijo
                    Compare_and_swap(shared_arr, i-1, i);
                    exit(0);
                }
                printf("  Comparando [%d]=%d y [%d]=%d\n", i-1, shared_arr[i-1], i, shared_arr[i]);
            }
        } else { // Fase impar
            for (int i = 1; i < n-1; i += 2) {
                pid_t pid = fork();
                if (pid == 0) { // Proceso hijo
                    Compare_and_swap(shared_arr, i, i+1);
                    exit(0);
                }
                printf("  Comparando [%d]=%d y [%d]=%d\n", i, shared_arr[i], i+1, shared_arr[i+1]);
            }
        }

        // Esperar a que todos los procesos hijos terminen
        while (wait(NULL) > 0);

        // Mostrar estado actual
        printf("  Estado actual: [");
        for (int j = 0; j < n; j++) {
            printf("%d", shared_arr[j]);
            if (j < n-1) printf(", ");
        }
        printf("]\n\n");
    }

    // Copiar datos de vuelta al arreglo original
    for (int i = 0; i < n; i++) {
        a[i] = shared_arr[i];
    }

    // Liberar memoria compartida
    munmap(shared_arr, n * sizeof(int));
}