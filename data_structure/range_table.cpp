#pragma once

#include <cstdint>

namespace range_table {

    constexpr std::int32_t log_2(std::int32_t);

    template <typename F>
    void for_all(std::int32_t sz, F f) {

        for (std::int32_t i = 0; i < sz; ++i) {
            f(0, i, 1);
        }

        for (std::int32_t i = 1; i <= log_2(sz); ++i) {
            const std::int32_t cur_sz = 1 << (i - 1);
            for (std::int32_t j = 0; j < sz >> i; ++j) {
                for (std::int32_t k = 1; k <= cur_sz; ++k) {
                    f(i, cur_sz * (j * 2 + 1) - k, k == 1);
                }
                for (std::int32_t k = 0; k < cur_sz; ++k) {
                    f(i, cur_sz * (j * 2 + 1) + k, k == 0);
                }
            }
        }

    }

    template <typename F>
    void for_rng(std::int32_t idx_l, std::int32_t idx_r, F f) {

        --idx_r;

        if (idx_l == idx_r) {
            f(0, idx_l);
            return;
        }

        const std::int32_t lvl = log_2(idx_l ^ idx_r) + 1;

        f(lvl, idx_l);
        f(lvl, idx_r);

    }

    constexpr std::int32_t log_2(std::int32_t x) {

        return 31 - __builtin_clz(x);

    }

}
