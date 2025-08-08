#include <cstdint>
#include <map>
#include <utility>
#include <vector>

#include "include/doctest.h"

#include "sequence/suffix_automaton.cpp"

TEST_CASE("suffix_automaton") {

    using mp_t = std::map<char, std::int32_t>;
    using vec_t = std::vector<std::int32_t>;

    suffix_automaton<char> sa(2);

    sa.extend('a');
    sa.extend('a');

    CHECK(sa.lens == vec_t({0, 1, 2, 0}));
    CHECK(sa.adj[0] == mp_t({std::make_pair('a', 1)}));
    CHECK(sa.adj[1] == mp_t({std::make_pair('a', 2)}));
    CHECK(sa.adj[2] == mp_t());
    CHECK(sa.links == vec_t({-1, 0, 1, 0}));
    CHECK(sa.idx == 3);

    sa = suffix_automaton<char>(3);

    sa.extend('a');
    sa.extend('b');
    sa.extend('a');

    CHECK(sa.lens == vec_t({0, 1, 2, 3, 0, 0}));
    CHECK(sa.adj[0] == mp_t({std::make_pair('a', 1), std::make_pair('b', 2)}));
    CHECK(sa.adj[1] == mp_t({std::make_pair('b', 2)}));
    CHECK(sa.adj[2] == mp_t({std::make_pair('a', 3)}));
    CHECK(sa.adj[3] == mp_t());
    CHECK(sa.links == vec_t({-1, 0, 0, 1, 0, 0}));
    CHECK(sa.idx == 4);

}
