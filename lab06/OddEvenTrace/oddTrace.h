/* File:    odd_even.c
 *
 * Purpose: Usar el algoritmo odd-even transposition sort para ordenar una lista de enteros.
 *
 * Compile: gcc -g -Wall -o odd_even odd_even.c
 * Run:     odd_even <n> <g|i>
 *             n:   número de elementos en la lista
 *            'g':  generar lista usando generador de números aleatorios
 *            'i':  ingresar lista manualmente
 *
 * Input:   lista (opcional)
 * Output:  lista ordenada
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Los valores en la lista aleatoria estarán en el rango 0 <= valor < RMAX */
const int RMAX = 100;

// Prototipos
void Usage(const char* prog_name);          // Muestra ayuda
void Get_args(int argc, char* argv[], int* n_p, char* g_i_p); // Procesa argumentos
void Generate_list(int a[], int n);        // Crea lista aleatoria
void Print_list(int a[], int n, const char* title); // Muestra lista
void Read_list(int a[], int n);            // Lee lista de usuario
void Odd_even_sort(int a[], int n);        // Algoritmo principal