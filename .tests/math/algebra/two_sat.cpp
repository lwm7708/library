#include <vector>

#include "include/doctest.h"

#include "math/algebra/two_sat.cpp"

TEST_CASE("two_sat") {

    two_sat slvr(3);

    slvr.add(0, 1, 1, 0);
    slvr.add(0, 0, 1, 1);
    slvr.add(0, 1, 1, 1);
    slvr.add(0, 0, 2, 1);

    auto res = slvr.solve();

    CHECK(res);

    const std::vector vars = *res;

    bool val = vars[0] || !vars[1];

    CHECK(val);

    val = !vars[0] || vars[1];

    CHECK(val);

    val = !vars[0] || !vars[1];

    CHECK(val);

    val = vars[0] || !vars[2];

    CHECK(val);

    slvr = two_sat(2);

    slvr.add(0, 0, 1, 0);
    slvr.add(0, 0, 1, 1);
    slvr.add(0, 1, 1, 0);
    slvr.add(0, 1, 1, 1);

    CHECK(!slvr.solve());

}
