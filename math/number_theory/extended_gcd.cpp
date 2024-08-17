#pragma once

#include <array>
#include <utility>

template <typename T>
std::array<T, 3> extended_gcd(T m, T n) {

    T a = 1;
    T a_in = 0;
    T b = 0;
    T b_in = 1;

    while (n) {
        const T q = m / n;
        a_in = std::exchange(a, a_in) - a_in * q;
        b_in = std::exchange(b, b_in) - b_in * q;
        n = std::exchange(m, n) - n * q;
    }

    return std::array<T, 3>({m, a, b});

}
