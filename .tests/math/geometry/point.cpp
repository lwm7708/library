#include <cmath>
#include <cstdint>
#include <cstdlib>

#include "include/doctest.h"

#include "math/geometry/point.cpp"

TEST_CASE("point") {

    using pt_t = point<std::int32_t>;

    constexpr double EPS = 1e-8;

    pt_t pt_1(2, -4);
    pt_t pt_2(7, 8);

    CHECK(pt_t::cross(pt_1, pt_2) == 44);
    CHECK(pt_t::dot(pt_1, pt_2) == -18);

    pt_1 += pt_2;

    CHECK(pt_1 == pt_t(9, 4));

    pt_1 -= pt_2;

    CHECK(pt_1 == pt_t(2, -4));

    pt_1 *= 3;

    CHECK(pt_1 == pt_t(6, -12));

    pt_1 /= 2;

    CHECK(pt_1 == pt_t(3, -6));

    CHECK(std::abs(pt_1.length() - std::sqrt(45)) < EPS);

    CHECK(pt_1.norm() == 45);

    pt_1 = pt_t(22, -4);
    pt_2 = pt_t(3, 4);

    CHECK(pt_1 == pt_t(22, -4));
    CHECK(pt_1 != pt_t());

    CHECK(pt_1 + pt_2 == pt_t(25, 0));
    CHECK(pt_1 - pt_2 == pt_t(19, -8));

    CHECK(pt_1 * 2 == pt_t(44, -8));
    CHECK(pt_1 / 2 == pt_t(11, -2));

}
