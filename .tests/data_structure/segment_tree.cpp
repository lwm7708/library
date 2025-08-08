#include <cstdint>
#include <deque>
#include <queue>

#include "include/doctest.h"

#include "data_structure/segment_tree.cpp"

TEST_CASE("segment_tree") {

    CHECK(segment_tree::log_2(11) == 3);
    CHECK(segment_tree::log_2(32) == 5);

    std::queue<std::int32_t> nds;

    nds.push(1);
    nds.push(3);
    nds.push(6);

    const auto pop = [&](std::int32_t nd) -> void {
        if (nds.front() == nd) {
            nds.pop();
        }
    };

    segment_tree::for_pars(13, 0, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(3);
    nds.push(1);

    segment_tree::for_pars(13, 1, pop);

    CHECK(std::empty(nds));

    nds.push(9);
    nds.push(12);
    nds.push(5);

    segment_tree::for_rng(9, 13, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(2);

    segment_tree::for_rng(4, 7, pop);

    CHECK(std::empty(nds));

    nds.push(9);
    nds.push(5);
    nds.push(12);

    segment_tree::for_rng_ord(9, 13, pop);

    CHECK(std::empty(nds));

    nds.push(2);
    nds.push(6);

    segment_tree::for_rng_ord(4, 7, pop);

    CHECK(std::empty(nds));

}
