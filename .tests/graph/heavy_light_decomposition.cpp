#include <array>
#include <cstdint>
#include <queue>
#include <vector>

#include "include/doctest.h"

#include "graph/heavy_light_decomposition.cpp"

TEST_CASE("heavy_light_decomposition") {

    using rng_t = std::array<std::int32_t, 2>;
    using vec_t = std::vector<std::int32_t>;

    heavy_light_decomposition decomp(11);

    decomp.add_edge(0, 1);
    decomp.add_edge(0, 2);
    decomp.add_edge(1, 3);
    decomp.add_edge(1, 4);
    decomp.add_edge(3, 5);
    decomp.add_edge(4, 6);
    decomp.add_edge(4, 7);
    decomp.add_edge(2, 8);
    decomp.add_edge(8, 9);
    decomp.add_edge(5, 10);

    decomp.init(0);

    CHECK(decomp.dfn == vec_t({0, 1, 8, 2, 5, 3, 6, 7, 9, 10, 4}));

    std::queue<rng_t> rngs;

    rngs.push(rng_t({7, 8}));
    rngs.push(rng_t({5, 6}));
    rngs.push(rng_t({1, 4}));

    const auto pop = [&](std::int32_t idx_l, std::int32_t idx_r) -> void {
        if (rngs.front() == rng_t({idx_l, idx_r})) {
            rngs.pop();
        }
    };

    decomp.for_path(5, 7, pop);

    CHECK(std::empty(rngs));

    rngs.push(rng_t({8, 11}));
    rngs.push(rng_t({0, 1}));

    decomp.for_path(9, 0, pop);

    decomp = heavy_light_decomposition(4);

    decomp.add_edge(2, 3);
    decomp.add_edge(3, 1);
    decomp.add_edge(0, 1);

    decomp.init(1);

    CHECK(decomp.dfn == vec_t({3, 0, 2, 1}));

    rngs.push(rng_t({1, 2}));

    decomp.for_path(3, 3, pop);

    CHECK(std::empty(rngs));

}
