#pragma once

#include <cstdint>
#include <type_traits>
#include <vector>

template <typename T>
bool miller_rabin(T n) {

    using int128_t = __int128_t;

    if (n < 2) {
        return false;
    }

    std::vector<std::int32_t> bases({2, 3, 5, 7});
    const std::int32_t s = __builtin_ctzll(n - 1);

    if (!std::is_same_v<T, std::int32_t>) {
        bases.insert(std::end(bases), {11, 13, 17, 19, 23, 29, 31, 37});
    }

    for (auto x : bases) {
        if (n == x) {
            return true;
        }
        T base = x;
        T d = (n - 1) >> s;
        T f = 1;
        const auto mul = [&](T& a, T b) -> void {
            a = (int128_t(a) * b) % n;
        };
        while (d) {
            if (d & 1) {
                mul(f, base);
            }
            d >>= 1;
            mul(base, base);
        }
        bool valid = f == 1;
        for (std::int32_t i = 0; i < s && !valid; ++i) {
            valid |= f == n - 1;
            mul(f, f);
        }
        if (!valid) {
            return false;
        }
    }

    return true;

}
