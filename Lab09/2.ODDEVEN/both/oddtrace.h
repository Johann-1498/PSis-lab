#ifndef ODD_TRACE_H
#define ODD_TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <thread>
#include <mutex>
#include <vector>
#include <cstring>

const int RMAX = 100;

// Prototipos
void Usage(const char* prog_name);
void Get_args(int argc, char* argv[], int* n_p, char* g_i_p, int* num_procs, int* num_threads);
void Generate_list(int a[], int n);
void Print_list(int a[], int n, const char* title);
void Read_list(int a[], int n);
void Odd_even_sort(int a[], int n);
void Phase_process(int* arr, int n, int phase, int num_threads);

#endif