#pragma once

#include <cstdint>

namespace fenwick_tree {

    template <typename F>
    void for_pars(std::int32_t nd, std::int32_t sz, F f) {

        ++nd;

        while (nd <= sz) {
            f(nd);
            nd += nd & -nd;
        }

    }

    template <typename F>
    void for_rng(std::int32_t nd, F f) {

        while (nd) {
            f(nd);
            nd -= nd & -nd;
        }

    }

}
