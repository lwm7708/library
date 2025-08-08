#include <array>
#include <numeric>

#include "include/doctest.h"

#include "math/number_theory/extended_gcd.cpp"

TEST_CASE("extended_gcd") {

    std::array res = extended_gcd(12, 27);

    CHECK(res[0] == std::gcd(12, 27));
    CHECK(res[1] * 12 + res[2] * 27 == res[0]);

    res = extended_gcd(37, 4);

    CHECK(res[0] == std::gcd(37, 4));
    CHECK(res[1] * 37 + res[2] * 4 == res[0]);

}
