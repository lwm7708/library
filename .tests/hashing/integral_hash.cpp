#include "include/doctest.h"

#include "hashing/integral_hash.cpp"

TEST_CASE("integral_hash") {

    const integral_hash hshr;

    CHECK(hshr(33) == hshr(33));
    CHECK(hshr(33) != hshr(89));
    CHECK(hshr(33) != hshr(-23));

}
