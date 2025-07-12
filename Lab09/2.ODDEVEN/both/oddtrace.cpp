#include "oddTrace.h"
#include <iostream>

void Usage(const char* prog_name) {
    fprintf(stderr, "uso: %s <n> <g|i> [num_procesos] [num_threads]\n", prog_name);
    fprintf(stderr, "   n: número de elementos\n");
    fprintf(stderr, "  'g': generar lista aleatoria\n");
    fprintf(stderr, "  'i': ingresar lista manualmente\n");
    fprintf(stderr, "  num_procesos: número de procesos (opcional, default=2)\n");
    fprintf(stderr, "  num_threads: hilos por proceso (opcional, default=2)\n");
}

void Get_args(int argc, char* argv[], int* n_p, char* g_i_p, int* num_procs, int* num_threads) {
    if (argc < 3) {
        Usage(argv[0]);
        exit(0);
    }
    
    *n_p = atoi(argv[1]);
    *g_i_p = argv[2][0];
    
    // Valores por defecto
    *num_procs = 2;
    *num_threads = 2;
    
    if (argc > 3) *num_procs = atoi(argv[3]);
    if (argc > 4) *num_threads = atoi(argv[4]);
 
    if (*n_p <= 0 || (*g_i_p != 'g' && *g_i_p != 'i')) {
        Usage(argv[0]);
        exit(0);
    }
}

void Generate_list(int a[], int n) {
    srand(time(NULL));
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

void Thread_compare(int* arr, int i, int j, std::mutex& mtx) {
    std::lock_guard<std::mutex> lock(mtx);
    if (arr[i] > arr[j]) {
        std::swap(arr[i], arr[j]);
    }
}

void Phase_process(int* arr, int n, int phase, int num_threads) {
    std::vector<std::thread> threads;
    std::mutex mtx;
    
    if (phase % 2 == 0) { // Fase par
        for (int i = 1; i < n; i += 2) {
            threads.emplace_back(Thread_compare, arr, i-1, i, std::ref(mtx));
            if (threads.size() >= num_threads) {
                for (auto& t : threads) t.join();
                threads.clear();
            }
        }
    } else { // Fase impar
        for (int i = 1; i < n-1; i += 2) {
            threads.emplace_back(Thread_compare, arr, i, i+1, std::ref(mtx));
            if (threads.size() >= num_threads) {
                for (auto& t : threads) t.join();
                threads.clear();
            }
        }
    }
    
    for (auto& t : threads) t.join();
}

void Odd_even_sort(int a[], int n) {
    int num_procs = 2;
    int num_threads = 2;
    
    // Crear memoria compartida
    int* shared_arr = (int*)mmap(NULL, n * sizeof(int),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_arr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    
    std::memcpy(shared_arr, a, n * sizeof(int));
    
    for (int phase = 0; phase < n; phase++) {
        printf("Fase %d (%s):\n", phase, (phase % 2 == 0) ? "par" : "impar");
        
        for (int p = 0; p < num_procs; p++) {
            pid_t pid = fork();
            if (pid == 0) { // Proceso hijo
                Phase_process(shared_arr, n, phase, num_threads);
                exit(EXIT_SUCCESS);
            } else if (pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
        
        // Esperar a todos los procesos hijos
        while (wait(NULL) > 0);
        
        // Mostrar estado actual
        printf("Estado actual: [");
        for (int j = 0; j < n; j++) {
            printf("%d", shared_arr[j]);
            if (j < n-1) printf(", ");
        }
        printf("]\n\n");
    }
    
    std::memcpy(a, shared_arr, n * sizeof(int));
    munmap(shared_arr, n * sizeof(int));
}