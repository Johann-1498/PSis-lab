#ifndef ODD_TRACE_H
#define ODD_TRACE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

const int RMAX = 100;

// Prototipos
void Usage(const char* prog_name);
void Get_args(int argc, char* argv[], int* n_p, char* g_i_p);
void Generate_list(int a[], int n);
void print(int a[], int n, const char* title);
void Read_list(int a[], int n);
void Odd_even_sort(int a[], int n);
void comp_swap(int a[], int i, int j, std::mutex& mtx);

// Clase ThreadPool
class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();

    void EnqueueJob(std::function<void()> job);

    std::queue<std::function<void()>> jobs;

private:
    void WorkerThread();

    size_t num_threads;
    std::vector<std::thread> worker_threads;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_all;
};

#endif
