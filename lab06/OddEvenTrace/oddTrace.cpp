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
   if (argc != 3) {                    // Verifica número de argumentos
      Usage(argv[0]);
      exit(0);
   }
   
   *n_p = atoi(argv[1]);               // Convierte tamaño a entero
   *g_i_p = argv[2][0];                // Obtiene modo (g/i)
 
   if (*n_p <= 0 || (*g_i_p != 'g' && *g_i_p != 'i')) {  // Valida argumentos
      Usage(argv[0]);
      exit(0);
   }
}

/*-----------------------------------------------------------------
 * Función:  Generate_list
 * Propósito: Generar lista aleatoria
 */
// Genera lista aleatoria con valores entre 0 y RMAX-1
void Generate_list(int a[], int n) {
   srand(0);                           // Semilla fija para reproducibilidad
   for (int i = 0; i < n; i++)
      a[i] = rand() % RMAX;            // Genera cada elemento
}

// Imprime la lista con un título descriptivo
void Print_list(int a[], int n, const char* title) {
   printf("%s:\n", title);             // Muestra título
   for (int i = 0; i < n; i++)         // Recorre cada elemento
      printf("%d ", a[i]);             // Imprime elemento
   printf("\n\n");                     // Salto de línea final
}

/*-----------------------------------------------------------------
 * Función:  Read_list
 * Propósito: Leer lista desde entrada estándar
 */
void Read_list(int a[], int n) {
   printf("Ingrese %d elementos:\n", n);
   for (int i = 0; i < n; i++)         // Para cada posición
      scanf("%d", &a[i]);              // Lee el valor
}

/*-----------------------------------------------------------------
 * Función:  Odd_even_sort
 * Propósito: Implementar el algoritmo odd-even sort con traza
 */
void Odd_even_sort(int a[], int n) {
   int phase, i, temp;

   // Bucle principal: n fases suficientes para ordenar
   for (phase = 0; phase < n; phase++) {
      printf("Fase %d (%s):\n", phase, (phase % 2 == 0) ? "par" : "impar");

      if (phase % 2 == 0) {            // Fase PAR
         for (i = 1; i < n; i += 2) {  // Compara pares de índices (0,1), (2,3)...
            printf("  Comparando [%d]=%d y [%d]=%d", i-1, a[i-1], i, a[i]);
            if (a[i-1] > a[i]) {       // Si están en orden incorrecto
               temp = a[i];            // Intercambia elementos
               a[i] = a[i-1];
               a[i-1] = temp;
               printf(" => swap\n");   // Muestra que hubo intercambio
            } else {
               printf(" => ok\n");     // Muestra que estaban en orden
            }
         }
      } else {                         // Fase IMPAR
         for (i = 1; i < n-1; i += 2) { // Compara pares (1,2), (3,4)...
            printf("  Comparando [%d]=%d y [%d]=%d", i, a[i], i+1, a[i+1]);
            if (a[i] > a[i+1]) {       // Si están en orden incorrecto
               temp = a[i];            // Intercambia elementos
               a[i] = a[i+1];
               a[i+1] = temp;
               printf(" => swap\n");   // Muestra que hubo intercambio
            } else {
               printf(" => ok\n");     // Muestra que estaban en orden
            }
         }
      }

      // Muestra el estado actual de la lista después de la fase
      printf("  Estado actual: [");
      for (int j = 0; j < n; j++) {
         printf("%d", a[j]);
         if (j < n-1) printf(", ");
      }
      printf("]\n\n");
   }
}