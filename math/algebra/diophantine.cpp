#pragma once

#include <array>
#include <cstdlib>
#include <optional>

#include "math/number_theory/extended_gcd.cpp"

template <typename T>
std::optional<std::array<T, 2>> diophantine(T a, T b, T c) {

    using arr_t = std::array<T, 2>;

    if (a == 0 && b == 0) {
        return c == 0 ? std::optional(arr_t()) : std::nullopt;
    }

    auto [dvsr, x, y] = extended_gcd(std::abs(a), std::abs(b));

    if (c % dvsr) {
        return std::nullopt;
    }

    x *= c / dvsr;
    y *= c / dvsr;

    if (a < 0) {
        x = -x;
    }

    if (b < 0) {
        y = -y;
    }

    return std::optional(arr_t({x, y}));

}
