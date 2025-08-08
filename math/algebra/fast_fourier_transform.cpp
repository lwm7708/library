#pragma once

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

template <typename T>
std::vector<T> fast_fourier_transform(
    const std::vector<T>& vec, std::int32_t inv, const std::vector<T>& rts
) {

    if (std::empty(vec)) {
        return std::vector<T>();
    }

    std::int32_t idx = 0;
    const std::int32_t sz = std::size(vec);
    std::vector vals = vec;

    for (std::int32_t i = 1; i < sz; ++i) {
        std::int32_t bit = sz >> 1;
        while (idx & bit) {
            idx ^= bit;
            bit >>= 1;
        }
        idx |= bit;
        if (i < idx) {
            std::swap(vals[i], vals[idx]);
        }
    }

    for (std::int32_t i = 2; i <= sz; i *= 2) {
        for (std::int32_t j = 0; j < sz; j += i) {
            T rt(1);
            for (std::int32_t k = j; k < j + i / 2; ++k) {
                const T val_1 = vals[k];
                const T val_2 = vals[k + i / 2] * rt;
                vals[k] = val_1 + val_2;
                vals[k + i / 2] = val_1 - val_2;
                rt *= rts[__builtin_ctz(i)];
            }
        }
    }

    if (inv) {
        std::reverse(std::begin(vals) + 1, std::end(vals));
        const T inverse = T(1) / T(sz);
        for (auto& x : vals) {
            x *= inverse;
        }
    }

    return vals;

}
