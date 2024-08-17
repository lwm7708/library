#pragma once

#include <cstdlib>

#include "math/number_theory/extended_gcd.cpp"

template <typename T>
auto diophantine(T a, T b, T c) {

    struct result {

        T x;
        T y;
        bool valid;

    };

    if (a == 0 && b == 0) {
        return result({0, 0, c == 0});
    }

    auto [dvsr, x, y] = extended_gcd(std::abs(a), std::abs(b));

    if (c % dvsr) {
        return result({0, 0, false});
    }

    x *= c / dvsr;
    y *= c / dvsr;

    if (a < 0) {
        x = -x;
    }

    if (b < 0) {
        y = -y;
    }

    return result({x, y, true});

}
