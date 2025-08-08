#include "include/doctest.h"

#include "data_structure/disjoint_set_union.cpp"

TEST_CASE("disjoint_set_union") {

    disjoint_set_union comps(4);

    CHECK(comps.find(0) == 0);
    CHECK(comps.find(1) == 1);
    CHECK(comps.find(2) == 2);
    CHECK(comps.find(3) == 3);

    comps.merge(0, 2);

    CHECK(comps.find(0) == comps.find(2));
    CHECK(comps.find(0) != comps.find(1));

    CHECK(comps.get_sz(0) == 2);

    comps.merge(2, 3);

    CHECK(comps.get_sz(1) == 1);
    CHECK(comps.get_sz(3) == 3);

    comps = disjoint_set_union(5);

    comps.merge(2, 3);
    comps.merge(3, 4);

    CHECK(comps.find(0) == 0);
    CHECK(comps.find(1) == 1);
    CHECK(comps.find(0) != comps.find(2));
    CHECK(comps.find(2) == comps.find(3));
    CHECK(comps.find(2) == comps.find(4));

    CHECK(comps.get_sz(0) == 1);
    CHECK(comps.get_sz(1) == 1);
    CHECK(comps.get_sz(2) == 3);
    CHECK(comps.get_sz(3) == 3);
    CHECK(comps.get_sz(4) == 3);

}
