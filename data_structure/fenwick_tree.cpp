#pragma once

#include <cstdint>

namespace fenwick_tree {

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
