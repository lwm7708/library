#include <cstdint>

#include "include/doctest.h"

#include "graph/dinic.cpp"

TEST_CASE("dinic") {

    dinic<std::int32_t> ntwk(6);

    ntwk.add_edge(0, 1, 7);
    ntwk.add_edge(0, 2, 4);
    ntwk.add_edge(2, 1, 3);
    ntwk.add_edge(1, 4, 3);
    ntwk.add_edge(1, 3, 5);
    ntwk.add_edge(2, 4, 2);
    ntwk.add_edge(4, 3, 3);
    ntwk.add_edge(4, 5, 5);
    ntwk.add_edge(3, 5, 8);

    CHECK(ntwk.push(0, 5) == 10);

    CHECK(ntwk.edges[7].second == 3);
    CHECK(ntwk.edges[9].second == 5);
    CHECK(ntwk.edges[11].second == 2);

    ntwk = dinic<std::int32_t>(4);

    ntwk.add_edge(2, 3, 4);
    ntwk.add_edge(3, 0, 4);
    ntwk.add_edge(0, 2, 4);
    ntwk.add_edge(2, 0, 2);
    ntwk.add_edge(0, 1, 7);

    CHECK(ntwk.push(2, 1) == 6);

    CHECK(ntwk.edges[1].second == 4);
    CHECK(ntwk.edges[3].second == 4);
    CHECK(ntwk.edges[5].second == 0);
    CHECK(ntwk.edges[7].second == 2);
    CHECK(ntwk.edges[9].second == 6);

}
