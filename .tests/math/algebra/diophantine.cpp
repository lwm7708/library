#include <optional>

#include "include/doctest.h"

#include "math/algebra/diophantine.cpp"

TEST_CASE("diophantine") {

    std::optional res = diophantine(0, 0, 0);

    CHECK(res);
    CHECK((*res)[0] * 0 + (*res)[1] * 0 == 0);

    res = diophantine(0, 0, 1);

    CHECK(!res);

    res = diophantine(3, 5, -1);

    CHECK(res);
    CHECK((*res)[0] * 3 + (*res)[1] * 5 == -1);

    res = diophantine(2, 4, -3);

    CHECK(!res);

    res = diophantine(3, 0, -9);

    CHECK(res);
    CHECK((*res)[0] * 3 + (*res)[1] * 0 == -9);

}
