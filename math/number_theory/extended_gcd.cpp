#pragma once

#include <array>
#include <utility>

template <typename T>
std::array<T, 3> extended_gcd(T m, T n) {

    T a_m = 1;
    T a_n = 0;
    T b_m = 0;
    T b_n = 1;

    while (n) {
        const T q = m / n;
        a_n = std::exchange(a_m, a_n) - a_n * q;
        b_n = std::exchange(b_m, b_n) - b_n * q;
        n = std::exchange(m, n) - n * q;
    }

    return std::array<T, 3>({m, a_m, b_m});

}
