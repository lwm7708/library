#pragma once

#include <cstdint>

namespace fenwick_tree {

    template <typename P>
    std::int32_t for_lvls(std::int32_t sz, P p) {

        std::int32_t idx = 0;

        for (std::int32_t i = 31 - __builtin_clz(sz); i >= 0; --i) {
            const std::int32_t n_idx = idx | 1 << i;
            if (n_idx <= sz && p(n_idx)) {
                idx = n_idx;
            }
        }

        return idx;

    }

    template <typename F>
    void for_pars(std::int32_t node, std::int32_t sz, F f) {

        ++node;

        while (node <= sz) {
            f(node);
            node += node & -node;
        }

    }

    template <typename F>
    void for_rng(std::int32_t node, F f) {

        while (node) {
            f(node);
            node -= node & -node;
        }

    }

}
