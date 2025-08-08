#include <array>
#include <cstdint>

#include "include/doctest.h"

#include "graph/minimum_cost_flow.cpp"

TEST_CASE("minimum_cost_flow") {

    minimum_cost_flow<std::int32_t> ntwk(5);

    ntwk.add_edge(0, 1, 3, 1);
    ntwk.add_edge(1, 4, 4, 1);
    ntwk.add_edge(2, 0, 3, 9);
    ntwk.add_edge(2, 3, 2, -2);
    ntwk.add_edge(3, 1, 8, 0);

    CHECK(ntwk.push(2, 4, 1) == std::array<std::int32_t, 2>({1, -1}));

    CHECK(ntwk.edges[1].cap == 0);
    CHECK(ntwk.edges[3].cap == 1);
    CHECK(ntwk.edges[5].cap == 0);
    CHECK(ntwk.edges[7].cap == 1);
    CHECK(ntwk.edges[9].cap == 1);

    ntwk = minimum_cost_flow<std::int32_t>(5);

    ntwk.add_edge(0, 1, 3, 1);
    ntwk.add_edge(1, 4, 4, 1);
    ntwk.add_edge(2, 0, 3, 9);
    ntwk.add_edge(2, 3, 2, -2);
    ntwk.add_edge(3, 1, 8, 0);
    ntwk.add_edge(2, 4, 1, 100);

    CHECK(ntwk.push(2, 4, 6) == std::array<std::int32_t, 2>({5, 120}));

    CHECK(ntwk.edges[1].cap == 2);
    CHECK(ntwk.edges[3].cap == 4);
    CHECK(ntwk.edges[5].cap == 2);
    CHECK(ntwk.edges[7].cap == 2);
    CHECK(ntwk.edges[9].cap == 2);

}
