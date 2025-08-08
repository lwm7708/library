#include "include/doctest.h"

#include "math/number_theory/miller_rabin.cpp"

TEST_CASE("miller_rabin") {

    CHECK(miller_rabin(2));
    CHECK(miller_rabin(7));
    CHECK(miller_rabin(7901));
    CHECK(miller_rabin(37139213));
    CHECK(miller_rabin(174440041));
    CHECK(miller_rabin(180252380737439));

    CHECK(!miller_rabin(1));
    CHECK(!miller_rabin(51));
    CHECK(!miller_rabin(129));
    CHECK(!miller_rabin(2048));
    CHECK(!miller_rabin(1437155053));
    CHECK(!miller_rabin(57882617207));

}
