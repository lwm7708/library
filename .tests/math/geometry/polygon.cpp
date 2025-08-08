#include <cmath>
#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "math/geometry/point.cpp"
#include "math/geometry/polygon.cpp"

TEST_CASE("polygon") {

    using plygn_t = polygon<std::int32_t>;
    using pt_t = point<std::int32_t>;

    constexpr double EPS = 1e-8;

    plygn_t plygn_1(3);
    const std::vector<pt_t> vtxs({pt_t(2, 0), pt_t(0, 2), pt_t(-2, 0), pt_t(0, -2)});

    plygn_1[1] = pt_t(1, 0);
    plygn_1[2] = pt_t(0, 1);

    CHECK(plygn_1.area() == 1);

    CHECK(std::abs(plygn_1.perim() - (2 + std::sqrt(2))) < EPS);

    CHECK(plygn_1.size() == 3);

    const plygn_t plygn_2(std::begin(vtxs), std::end(vtxs));

    CHECK(plygn_2.area() == 16);

    CHECK(std::abs(plygn_2.perim() - (2 * std::sqrt(2)) * 4) < EPS);

    CHECK(plygn_2.contains(pt_t()) == 1);
    CHECK(plygn_2.contains(pt_t(3, 0)) == 0);
    CHECK(plygn_2.contains(pt_t(2, 2)) == 0);
    CHECK(plygn_2.contains(pt_t(-2, 0)) == 2);
    CHECK(plygn_2.contains(pt_t(-1, 1)) == 2);

    CHECK(plygn_2.size() == 4);

}
