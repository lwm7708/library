#include "include/doctest.h"

#include "math/number_theory/modular_congruence.cpp"

TEST_CASE("modular_congruence") {

    modular_congruence cong(3, 1);

    cong &= modular_congruence(2, 0);

    CHECK(cong.m == 6);
    CHECK(cong.a == 4);

    cong &= modular_congruence(5, 1);

    CHECK(cong.m == 30);
    CHECK(cong.a == 16);

    cong &= modular_congruence(4, 3);

    CHECK(cong.m == 0);

    cong = modular_congruence(6, 3) & modular_congruence(8, 5);

    CHECK(cong.m == 24);
    CHECK(cong.a == 21);

}
