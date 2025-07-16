#include "oddtrace.h"
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

void Thread_compare(int* arr, int i, int j) {
    if (arr[i] > arr[j]) {
        std::swap(arr[i], arr[j]);
    }
}

void Phase_process(int* arr, int n, int phase, int num_threads) {
    std::vector<std::thread> threads;
    
    auto worker = [&](int start, int end) {
        if (phase % 2 == 0) {
            for (int i = start; i < end; i += 2) {
                if (i + 1 < n) Thread_compare(arr, i, i + 1);
            }
        } else {
            for (int i = start; i < end; i += 2) {
                if (i + 1 < n) Thread_compare(arr, i, i + 1);
            }
        }
    };

    int chunk_size = std::max(1, n / num_threads);
    for (int t = 0; t < num_threads; ++t) {
        int start = t * chunk_size;
        int end = (t == num_threads - 1) ? n : (t + 1) * chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& t : threads) t.join();
}

void Odd_even_sort(int a[], int n, int num_procs, int num_threads) {
    int* shared_arr = (int*)mmap(NULL, n * sizeof(int),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_arr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    
    std::memcpy(shared_arr, a, n * sizeof(int));
    
    for (int phase = 0; phase < n; phase++) {
        for (int p = 0; p < num_procs; p++) {
            pid_t pid = fork();
            if (pid == 0) {
                Phase_process(shared_arr, n, phase, num_threads);
                _exit(EXIT_SUCCESS);  // Usar _exit en hijos
            } else if (pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
        }
        
        while (wait(NULL) > 0);
    }
    
    std::memcpy(a, shared_arr, n * sizeof(int));
    munmap(shared_arr, n * sizeof(int));
}
