#pragma once

#include <cstdint>

namespace segment_tree {

    constexpr std::int32_t log_2(std::int32_t);

    template <typename F>
    void for_pars(std::int32_t nd, std::int32_t dir, F f) {

        const std::int32_t lvls = log_2(nd);

        for (std::int32_t i = 1; i <= lvls; ++i) {
            f(nd >> (dir == 0 ? lvls - i + 1 : i));
        }

    }

    template <typename F>
    void for_rng(std::int32_t nd_l, std::int32_t nd_r, F f) {

        while (nd_l < nd_r) {
            if (nd_l & 1) {
                f(nd_l);
                ++nd_l;
            }
            if (nd_r & 1) {
                --nd_r;
                f(nd_r);
            }
            nd_l >>= 1;
            nd_r >>= 1;
        }

    }

    template <typename F>
    void for_rng_ord(std::int32_t nd_l, std::int32_t nd_r, F f) {

        if (nd_r - nd_l <= 0) {
            return;
        }

        const std::int32_t msk = (1 << log_2((nd_l - 1) ^ nd_r)) - 1;

        std::int32_t nd = -nd_l & msk;

        while (nd) {
            const std::int32_t bit = __builtin_ctz(nd);
            f(((nd_l - 1) >> bit) + 1);
            nd ^= 1 << bit;
        }

        nd = nd_r & msk;

        while (nd) {
            const std::int32_t bit = log_2(nd);
            f((nd_r >> bit) - 1);
            nd ^= 1 << bit;
        }

    }

    constexpr std::int32_t log_2(std::int32_t x) {

        return 31 - __builtin_clz(x);

    }

}
