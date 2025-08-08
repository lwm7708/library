#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "math/number_theory/sieve.cpp"

TEST_CASE("sieve") {

    sieve::reserve(50);

    CHECK(sieve::facts[2] == 2);
    CHECK(sieve::facts[5] == 5);
    CHECK(sieve::facts[9] == 3);
    CHECK(sieve::facts[13] == 13);
    CHECK(sieve::facts[21] == 3);
    CHECK(sieve::facts[25] == 5);
    CHECK(sieve::facts[31] == 31);
    CHECK(sieve::facts[49] == 7);

    CHECK(
        sieve::primes == std::vector<std::int32_t>(
            {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}
        )
    );

}
