#include <cstdint>

#include "include/doctest.h"

#include "math/number_theory/pollard_rho.cpp"

TEST_CASE("pollard_rho") {

    std::int64_t dvsr = pollard_rho(51);

    CHECK(dvsr != 51);
    CHECK(51 % dvsr == 0);

    dvsr = pollard_rho(129);

    CHECK(dvsr != 129);
    CHECK(129 % dvsr == 0);

    dvsr = pollard_rho(2048);

    CHECK(dvsr != 2048);
    CHECK(2048 % dvsr == 0);

    dvsr = pollard_rho(1437155053);

    CHECK(dvsr != 1437155053);
    CHECK(1437155053 % dvsr == 0);

    dvsr = pollard_rho(57882617207);

    CHECK(dvsr != 57882617207);
    CHECK(57882617207 % dvsr == 0);

}
