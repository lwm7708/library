#pragma once

#include <array>
#include <cstdlib>
#include <optional>

#include "math/number_theory/extended_gcd.cpp"

template <typename T>
std::optional<std::array<T, 2>> diophantine(T a, T b, T c) {

    using arr_t = std::array<T, 2>;

    using ret_t = std::optional<arr_t>;

    if (a == 0 && b == 0) {
        return c == 0 ? ret_t(arr_t()) : ret_t();
    }

    auto [dvsr, x, y] = extended_gcd(std::abs(a), std::abs(b));

    if (c % dvsr) {
        return ret_t();
    }

    x *= c / dvsr;
    y *= c / dvsr;

    if (a < 0) {
        x = -x;
    }

    if (b < 0) {
        y = -y;
    }

    return ret_t(arr_t({x, y}));

}
