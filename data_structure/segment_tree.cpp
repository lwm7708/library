#pragma once

#include <cstdint>

namespace segment_tree {

    constexpr std::int32_t log_2(std::int32_t);

    template <typename F>
    void for_pars(std::int32_t node, bool dir, F f) {

        const std::int32_t lvls = log_2(node);

        for (std::int32_t i = 1; i <= lvls; ++i) {
            f(node >> (!dir ? lvls - i + 1 : i));
        }

    }

    template <typename F>
    void for_rng(std::int32_t node_l, std::int32_t node_r, F f) {

        while (node_l < node_r) {
            if (node_l & 1) {
                f(node_l);
                ++node_l;
            }
            if (node_r & 1) {
                --node_r;
                f(node_r);
            }
            node_l >>= 1;
            node_r >>= 1;
        }

    }

    template <typename F>
    void for_rng_ord(std::int32_t node_l, std::int32_t node_r, bool dir, F f) {

        std::int32_t base = !dir ? node_l - 1 : node_r;
        const std::int32_t mask = (1 << log_2((node_l - 1) ^ node_r)) - 1;
        const std::int32_t shft = !dir ? 1 : -1;

        std::int32_t node = (!dir ? -node_l : node_r) & mask;

        while (node) {
            const std::int32_t bit = __builtin_ctz(node);
            f((base >> bit) + shft);
            node ^= 1 << bit;
        }

        base = dir ? node_l - 1 : node_r;
        node = (dir ? -node_l : node_r) & mask;

        while (node) {
            const std::int32_t bit = log_2(node);
            f((base >> bit) - shft);
            node ^= 1 << bit;
        }

    }

    constexpr std::int32_t log_2(std::int32_t x) {

        return 31 - __builtin_clz(x);

    }

}
