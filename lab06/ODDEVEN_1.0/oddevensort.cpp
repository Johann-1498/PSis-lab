#include "OddEvenSort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

OddEvenSorter::OddEvenSorter(int n) {
    list.resize(n);
}

void OddEvenSorter::generateList() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (auto& x : list)
        x = std::rand() % RMAX;
}

void OddEvenSorter::readList() {
    std::cout << "Please enter the elements of the list:\n";
    for (auto& x : list)
        std::cin >> x;
}

void OddEvenSorter::printList(const std::string& title) const {
    std::cout << title << ":\n";
    for (const auto& x : list)
        std::cout << x << " ";
    std::cout << "\n\n";
}

void OddEvenSorter::printCurrentStep(int phase) const {
    std::cout << "Phase " << phase << ": ";
    for (const auto& x : list)
        std::cout << x << " ";
    std::cout << "\n";
}

void OddEvenSorter::sort() {
    int n = list.size();

    for (int phase = 0; phase < n; ++phase) {
        std::vector<std::thread> threads;
        std::mutex swap_mutex;

        if (phase % 2 == 0) { // Even phase
            for (int i = 1; i < n; i += 2) {
                threads.emplace_back([&, i]() {
                    std::lock_guard<std::mutex> lock(swap_mutex);
                    if (list[i - 1] > list[i]) {
                        std::swap(list[i - 1], list[i]);
                    }
                });
            }
        } else { // Odd phase
            for (int i = 1; i < n - 1; i += 2) {
                threads.emplace_back([&, i]() {
                    std::lock_guard<std::mutex> lock(swap_mutex);
                    if (list[i] > list[i + 1]) {
                        std::swap(list[i], list[i + 1]);
                    }
                });
            }
        }

        for (auto& t : threads) {
            if (t.joinable())
                t.join();
        }

        printCurrentStep(phase);
    }

    std::cout << "\n";
}
