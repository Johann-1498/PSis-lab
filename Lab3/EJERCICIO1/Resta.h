#ifndef RESTA_H
#define RESTA_H

#include "Operacion.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Resta : public Operacion<T> {
public:
    T ejecutar(const T& a, const T& b) override {
        return a - b;
    }
};

template<typename T>
class Resta<std::vector<T>> : public Operacion<std::vector<T>> {
public:
    std::vector<T> ejecutar(const std::vector<T>& a,
                            const std::vector<T>& b) override {
        std::vector<T> r;
        size_t n = std::min(a.size(), b.size());
        r.reserve(n);
        for (size_t i = 0; i < n; ++i) r.push_back(a[i] - b[i]);
        return r;
    }
};

template<typename T>
class Resta<std::vector<std::vector<T>>> : public Operacion<std::vector<std::vector<T>>> {
public:
    std::vector<std::vector<T>> ejecutar(
        const std::vector<std::vector<T>>& A,
        const std::vector<std::vector<T>>& B) override
    {
        size_t f = A.size(), c = A.empty() ? 0 : A[0].size();
        if (f != B.size() || c != B[0].size())
            throw std::runtime_error("Dimensiones invalidas");
        std::vector<std::vector<T>> R(f, std::vector<T>(c));
        for (size_t i = 0; i < f; ++i)
            for (size_t j = 0; j < c; ++j)
                R[i][j] = A[i][j] - B[i][j];
        return R;
    }
};

#endif 
