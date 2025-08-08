#include <cmath>
#include <cstdint>

#include "include/doctest.h"

#include "math/geometry/point.cpp"
#include "math/geometry/segment.cpp"

TEST_CASE("segment") {

    using pt_t = point<std::int32_t>;
    using seg_t = segment<std::int32_t>;

    constexpr double EPS = 1e-8;

    const seg_t seg(pt_t(4, 0), pt_t(0, 2));

    CHECK(!seg_t::intersects(seg, seg_t(pt_t(2, -2), pt_t(-2, 2))));
    CHECK(seg_t::intersects(seg, seg_t(pt_t(-2, -1), pt_t(0, 2))));
    CHECK(seg_t::intersects(seg, seg_t(pt_t(), pt_t(2, 2))));

    CHECK(std::abs(seg.length() - std::sqrt(20)) < EPS);

    CHECK(seg.norm() == 20);

}
