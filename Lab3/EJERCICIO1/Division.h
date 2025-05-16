#ifndef DIVISION_H
#define DIVISION_H

#include "Operacion.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Division : public Operacion<T> {
public:
    T ejecutar(const T& a, const T& b) override {
        if (b == T(0)) throw std::runtime_error("Division por cero");
        return a / b;
    }
};

template<typename T>
class Division<std::vector<T>> : public Operacion<std::vector<T>> {
public:
    std::vector<T> ejecutar(const std::vector<T>& a,
                            const std::vector<T>& b) override {
        std::vector<T> r;
        size_t n = std::min(a.size(), b.size());
        r.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            if (b[i] == T(0))
                throw std::runtime_error("Division por cero en vector");
            r.push_back(a[i] / b[i]);
        }
        return r;
    }
};

template<typename T>
class Division<std::vector<std::vector<T>>> : public Operacion<std::vector<std::vector<T>>> {
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
            for (size_t j = 0; j < c; ++j) {
                if (B[i][j] == T(0))
                    throw std::runtime_error("Division por cero en matriz");
                R[i][j] = A[i][j] / B[i][j];
            }
        return R;
    }
};

#endif // DIVISION_H
