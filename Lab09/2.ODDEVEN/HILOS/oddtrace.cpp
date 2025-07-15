#include "oddtrace.h"
#include <iostream>
#include <functional>

ThreadPool::ThreadPool(size_t num_threads) : num_threads(num_threads), stop_all(false) {
    worker_threads.reserve(num_threads);
    for (size_t i = 0; i < num_threads; ++i) {
        worker_threads.emplace_back([this]() { this->WorkerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop_all = true;
    }
    cv.notify_all();
    
    for (auto& t : worker_threads) {
        t.join();
    }
}

void ThreadPool::WorkerThread() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !this->jobs.empty() || stop_all; });
            
            if (stop_all && this->jobs.empty()) {
                return;
            }
            
            job = std::move(jobs.front());
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::EnqueueJob(std::function<void()> job) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        jobs.push(std::move(job));
    }
    cv.notify_one();
}

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

void print(int a[], int n, const char* title) {
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

void Odd_even_sort(int a[], int n) {
    // Crear pool de hilos (número de hilos = número de núcleos - 1)
    unsigned int num_threads = std::thread::hardware_concurrency() - 1;
    if (num_threads == 0) num_threads = 1;  // Mínimo 1 hilo
    ThreadPool pool(num_threads);
    
    std::mutex mtx;
    
    for (int phase = 0; phase < n; phase++) {
        printf("Fase %d (%s):\n", phase, (phase % 2 == 0) ? "par" : "impar");
        
        if (phase % 2 == 0) { // Fase par
            for (int i = 1; i < n; i += 2) {
                pool.EnqueueJob([&a, i, &mtx]() {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (a[i-1] > a[i]) {
                        int temp = a[i];
                        a[i] = a[i-1];
                        a[i-1] = temp;
                    }
                });
                printf("  Comparando [%d]=%d y [%d]=%d\n", i-1, a[i-1], i, a[i]);
            }
        } else { // Fase impar
            for (int i = 1; i < n-1; i += 2) {
                pool.EnqueueJob([&a, i, &mtx]() {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (a[i] > a[i+1]) {
                        int temp = a[i];
                        a[i] = a[i+1];
                        a[i+1] = temp;
                    }
                });
                printf("  Comparando [%d]=%d y [%d]=%d\n", i, a[i], i+1, a[i+1]);
            }
        }
        
        // Esperar a que todas las tareas se completen
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            if (pool.jobs.empty()) break;
        }

        // Mostrar estado actual
        printf("  Estado actual: [");
        for (int j = 0; j < n; j++) {
            printf("%d", a[j]);
            if (j < n-1) printf(", ");
        }
        printf("]\n\n");
    }
}
