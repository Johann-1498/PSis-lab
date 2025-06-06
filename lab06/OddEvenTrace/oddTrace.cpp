#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "oddTrace.h"

/*-----------------------------------------------------------------
 * Función:  Usage
 * Propósito: Mostrar cómo ejecutar el programa
 */
void Usage(const char* prog_name) {
   fprintf(stderr, "uso:   %s <n> <g|i>\n", prog_name);
   fprintf(stderr, "   n:   numero de elementos en la lista\n");
   fprintf(stderr, "  'g':  generar lista aleatoria\n");
   fprintf(stderr, "  'i':  ingresar lista manualmente\n");
}

/*-----------------------------------------------------------------
 * Función:  Get_args
 * Propósito: Obtener y validar argumentos de línea de comandos
 */
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

/*-----------------------------------------------------------------
 * Función:  Generate_list
 * Propósito: Generar lista aleatoria
 */
void Generate_list(int a[], int n) {
   srand(0);
   for (int i = 0; i < n; i++)
      a[i] = rand() % RMAX;
}

/*-----------------------------------------------------------------
 * Función:  Print_list
 * Propósito: Imprimir la lista
 */
void Print_list(int a[], int n, const char* title) {
   printf("%s:\n", title);
   for (int i = 0; i < n; i++)
      printf("%d ", a[i]);
   printf("\n\n");
}

/*-----------------------------------------------------------------
 * Función:  Read_list
 * Propósito: Leer lista desde entrada estándar
 */
void Read_list(int a[], int n) {
   printf("Ingrese %d elementos:\n", n);
   for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
}

/*-----------------------------------------------------------------
 * Función:  Odd_even_sort
 * Propósito: Implementar el algoritmo odd-even sort con traza
 */
void Odd_even_sort(int a[], int n) {
   int phase, i, temp;

   for (phase = 0; phase < n; phase++) {
      printf("Fase %d (%s):\n", phase, (phase % 2 == 0) ? "par" : "impar");

      if (phase % 2 == 0) { // Fase par
         for (i = 1; i < n; i += 2) {
            printf("  Comparando posiciones %d-%d: [%d]-[%d]", 
                  i-1, i, a[i-1], a[i]);
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
               printf(" => swap\n");
            } else {
               printf(" => ok\n");
            }
         }
      } else { // Fase impar
         for (i = 1; i < n-1; i += 2) {
            printf("  Comparando posiciones %d-%d: [%d]-[%d]", 
                  i, i+1, a[i], a[i+1]);
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
               printf(" => swap\n");
            } else {
               printf(" => ok\n");
            }
         }
      }

      printf("  Lista despues de fase %d: [", phase);
      for (int j = 0; j < n; j++) {
         printf("%d", a[j]);
         if (j < n-1) printf(", ");
      }
      printf("]\n\n");
   }
}