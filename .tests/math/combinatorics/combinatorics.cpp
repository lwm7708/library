#include <cstdint>

#include "include/doctest.h"

#include "math/combinatorics/combinatorics.cpp"
#include "math/number_theory/modular_integer.cpp"

TEST_CASE("combinatorics") {

    static constexpr std::int32_t MOD = 53;

    combinatorics<modular_integer<MOD>> comb;

    comb.reserve(60);

    CHECK(comb.comb(2, 3).val == 0);
    CHECK(comb.comb(2, -1).val == 0);
    CHECK(comb.comb(8, 3).val == 3);
    CHECK(comb.comb(51, 8).val == 9);

    CHECK(comb.fact(-3).val == 0);
    CHECK(comb.fact(8).val == 40);
    CHECK(comb.fact(51).val == 1);

    CHECK(comb.inv(-3).val == 0);
    CHECK(comb.inv(8).val == 20);
    CHECK(comb.inv(51).val == 26);

    CHECK(comb.inv_fact(-3).val == 0);
    CHECK(comb.inv_fact(8).val == 4);
    CHECK(comb.inv_fact(51).val == 1);

}
