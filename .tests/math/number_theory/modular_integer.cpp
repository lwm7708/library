#include <optional>

#include "include/doctest.h"

#include "math/number_theory/modular_integer.cpp"

TEST_CASE("modular_integer") {

    using num_t = modular_integer<53>;

    CHECK(num_t(2) == num_t(108));
    CHECK(num_t(-2) == num_t(51));
    CHECK((-num_t(2)) == num_t(51));

    num_t num_1(51);
    num_t num_2;
    std::optional res = num_t().sqrt();

    ++num_1;
    --num_2;

    CHECK(num_1.val == 52);
    CHECK(num_2.val == 52);

    ++num_1;

    CHECK(num_1.val == 0);

    num_1 += num_2 * num_t(2);

    CHECK(num_1.val == 51);

    num_1 -= num_t(-1);

    CHECK(num_1.val == 52);

    num_1 *= num_t(3);

    CHECK(num_1.val == 50);

    num_1 /= num_t(3);

    CHECK(num_1.val == 52);

    CHECK(res);
    CHECK(res->val == 0);

    res = num_t(3).sqrt();

    CHECK(!res);

    res = num_t(7).sqrt();

    CHECK(res);
    CHECK(res->val == 22);

    res = num_t(49).sqrt();

    CHECK(res);
    CHECK(res->val == 7);

    res = num_t(52).sqrt();

    CHECK(res);
    CHECK(res->val == 23);

    CHECK(num_t(-2) == num_t(51));
    CHECK(num_t(-2) != num_t(2));

    CHECK((num_t(-2) + num_t(-3)).val == 48);
    CHECK((num_t(-2) - num_t(-3)).val == 1);
    CHECK((num_t(-2) * num_t(3)).val == 47);
    CHECK((num_t(-2) / num_t(3)).val == 17);

}
