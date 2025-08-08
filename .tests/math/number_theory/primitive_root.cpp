#include "include/doctest.h"

#include "math/number_theory/primitive_root.cpp"

TEST_CASE("primitive_root") {

    CHECK(primitive_root(998244353) == 3);
    CHECK(primitive_root(754974721) == 11);
    CHECK(primitive_root(1000000007) == 5);

}
