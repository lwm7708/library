#include <array>
#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "sequence/aho_corasick_automaton.cpp"

TEST_CASE("aho_corasick_automaton") {

    using arr_t = std::array<std::int32_t, 3>;
    using vec_t = std::vector<std::int32_t>;

    aho_corasick_automaton<3> ac;

    ac.extend(0);
    ac.extend(1);

    ac.ptr = 0;

    ac.extend(0);
    ac.extend(1);
    ac.extend(0);

    ac.ptr = 0;

    ac.extend(1);

    ac.init();

    CHECK(ac.adj[0] == arr_t({1, 4, 0}));
    CHECK(ac.adj[1] == arr_t({1, 2, 0}));
    CHECK(ac.adj[2] == arr_t({3, 4, 0}));
    CHECK(ac.adj[3] == arr_t({1, 2, 0}));
    CHECK(ac.adj[4] == arr_t({1, 4, 0}));
    CHECK(ac.links == vec_t({0, 0, 4, 1, 0}));

    ac = aho_corasick_automaton<3>();

    ac.extend(0);
    ac.extend(0);

    ac.ptr = 0;

    ac.extend(1);

    ac.ptr = 0;

    ac.extend(2);

    ac.init();

    CHECK(ac.adj[0] == arr_t({1, 3, 4}));
    CHECK(ac.adj[1] == arr_t({2, 3, 4}));
    CHECK(ac.adj[2] == arr_t({2, 3, 4}));
    CHECK(ac.adj[3] == arr_t({1, 3, 4}));
    CHECK(ac.adj[4] == arr_t({1, 3, 4}));
    CHECK(ac.links == vec_t({0, 0, 1, 0, 0}));

}
