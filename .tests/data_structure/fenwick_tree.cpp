#include <cstdint>
#include <deque>
#include <queue>

#include "include/doctest.h"

#include "data_structure/fenwick_tree.cpp"

TEST_CASE("fenwick_tree") {

    std::queue<std::int32_t> nds;

    nds.push(3);
    nds.push(4);
    nds.push(8);

    const auto pop = [&](std::int32_t nd) -> void {
        if (nd == nds.front()) {
            nds.pop();
        }
    };

    fenwick_tree::for_pars(2, 8, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(8);

    fenwick_tree::for_pars(5, 8, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(4);

    fenwick_tree::for_rng(6, pop);

    CHECK(std::empty(nds));

    nds.push(7);
    nds.push(6);
    nds.push(4);

    fenwick_tree::for_rng(7, pop);

    CHECK(std::empty(nds));

}
