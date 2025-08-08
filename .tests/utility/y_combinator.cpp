#include <cstdint>
#include <numeric>

#include "include/doctest.h"

#include "utility/y_combinator.cpp"

TEST_CASE("y_combinator") {

    const auto gcd = y_combinator(
        [&](auto self, std::int32_t m, std::int32_t n) -> std::int32_t {
            return n ? self(n, m % n) : m;
        }
    );

    CHECK(gcd(18, 42) == std::gcd(18, 42));
    CHECK(gcd(64, 127) == std::gcd(64, 127));
    CHECK(gcd(0, 3) == std::gcd(0, 3));

}
