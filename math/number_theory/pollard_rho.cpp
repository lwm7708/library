#pragma once

#include <cstdint>
#include <numeric>

std::int64_t pollard_rho(std::int64_t n) {

    using int128_t = __int128_t;

    if (n % 2 == 0) {
        return 2;
    }

    std::int64_t c = 1;
    std::int64_t dvsr = 1;

    const auto f = [&](std::int64_t x) -> std::int64_t {
        return (int128_t(x) * x + c) % n;
    };

    while (dvsr == 1 || dvsr == n) {
        dvsr = 1;
        std::int64_t ptr_1 = c;
        std::int64_t ptr_2 = f(c);
        while (dvsr == 1) {
            dvsr = std::gcd(ptr_2 - ptr_1, n);
            ptr_1 = f(ptr_1);
            ptr_2 = f(f(ptr_2));
        }
        ++c;
    }

    return dvsr;

}
