#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "graph/long_path_decomposition.cpp"

TEST_CASE("long_path_decomposition") {

    using vec_t = std::vector<std::int32_t>;

    long_path_decomposition decomp(11);

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
    CHECK(decomp.chds == vec_t({1, 3, 8, 5, 6, 10, -1, -1, 9, -1, -1}));
    CHECK(decomp.deps == vec_t({4, 3, 2, 2, 1, 1, 0, 0, 1, 0, 0}));

    decomp = long_path_decomposition(4);

    decomp.add_edge(2, 3);
    decomp.add_edge(3, 1);
    decomp.add_edge(0, 1);

    decomp.init(1);

    CHECK(decomp.dfn == vec_t({3, 0, 2, 1}));
    CHECK(decomp.chds == vec_t({-1, 3, -1, 2}));
    CHECK(decomp.deps == vec_t({0, 2, 0, 1}));

}
