#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int n, const char *phase, int child_pid) {
    printf("[PID %d -> %d] %s: ", getpid(), child_pid, phase);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

bool is_sorted(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void odd_even_sort(int *arr, int n) {
    int step = 1;

    printf("Proceso padre (PID principal): %d\n", getpid());
    printf("================================\n");

    // Continuar hasta que el arreglo esté completamente ordenado
    while (!is_sorted(arr, n)) {
        printf("\n=== Iteración %d ===\n", step++);

        // Odd phase
        for (int i = 1; i < n - 1; i += 2) {
            pid_t pid = fork();
            if (pid == 0) {
                printf("\n[Proceso hijo] PID %d (padre %d) compara %d y %d\n",
                       getpid(), getppid(), arr[i], arr[i + 1]);

                if (arr[i] > arr[i + 1]) {
                    swap(&arr[i], &arr[i + 1]);
                    printf("  -> Intercambio: %d ↔ %d\n", arr[i + 1], arr[i]);
                }
                _exit(0);
            } else {
                wait(NULL); // El padre espera a que el hijo termine
                print_array(arr, n, "Odd", pid);
            }
        }

        // Even phase
        for (int i = 0; i < n - 1; i += 2) {
            pid_t pid = fork();
            if (pid == 0) {
                printf("\n[Proceso hijo] PID %d (padre %d) compara %d y %d\n",
                       getpid(), getppid(), arr[i], arr[i + 1]);

                if (arr[i] > arr[i + 1]) {
                    swap(&arr[i], &arr[i + 1]);
                    printf("  -> Intercambio: %d ↔ %d\n", arr[i + 1], arr[i]);
                }
                _exit(0);
            } else {
                wait(NULL); // El padre espera a que el hijo termine
                print_array(arr, n, "Even", pid);
            }
        }
    }

    printf("\n=== Resultado final ===\n");
    print_array(arr, n, "Ordenado", 0);
}

int main() {
    int n;
    printf("Ingrese tamaño del arreglo: ");
    scanf("%d", &n);

    // Crear arreglo en memoria compartida
    int *arr = mmap(NULL, n * sizeof(int), PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (arr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Ingrese %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\n=== Inicio del ordenamiento ===\n");
    odd_even_sort(arr, n);

    // Liberar memoria compartida
    munmap(arr, n * sizeof(int));

    return 0;
}
