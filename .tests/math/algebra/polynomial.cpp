#include <cstdint>
#include <optional>
#include <vector>

#include "include/doctest.h"

#include "math/algebra/polynomial.cpp"
#include "math/number_theory/modular_integer.cpp"

TEST_CASE("polynomial") {

    static constexpr std::int32_t MOD = 998244353;
    static constexpr std::int32_t PRT = 3;

    using num_t = modular_integer<MOD>;

    using poly_t = polynomial<num_t, PRT>;

    poly_t poly_1({num_t(3), num_t(2), num_t()});
    poly_t poly_2(3);
    const poly_t poly_3({num_t(), num_t(12), num_t(-13), num_t(-14)});
    std::vector xs({num_t(3), num_t(), num_t(-1), num_t(2)});
    std::vector ys({num_t(108), num_t(3), num_t(8), num_t(29)});

    CHECK(poly_1.size() == 3);
    CHECK(poly_2.size() == 3);

    poly_1.trim();

    CHECK(poly_1.size() == 2);

    CHECK(poly_1[0].val == 3);
    CHECK(poly_1[1].val == 2);

    poly_2[0] = num_t(-2);
    poly_2[1] = num_t(7);

    poly_2.trim();

    CHECK(-poly_2 == poly_t({num_t(2), num_t(-7)}));

    poly_1 += poly_2;

    CHECK(poly_1 == poly_t({num_t(1), num_t(9)}));

    poly_1 -= poly_2;

    CHECK(poly_1 == poly_t({num_t(3), num_t(2)}));

    poly_1 *= poly_2;

    CHECK(poly_1 == poly_t({num_t(-6), num_t(17), num_t(14)}));

    poly_1 /= poly_2;

    CHECK(poly_1 == poly_t({num_t(3), num_t(2)}));

    poly_1 *= num_t(-2);

    CHECK(poly_1 == poly_t({num_t(-6), num_t(-4)}));

    poly_1 /= num_t(-2);

    CHECK(poly_1 == poly_t({num_t(3), num_t(2)}));

    poly_1 %= poly_t({num_t(-1), num_t(1)});

    CHECK(poly_1 == poly_t({num_t(5)}));

    poly_1 = poly_t({num_t(3), num_t(-7), num_t(2), num_t(4)});

    CHECK(poly_1.eval(num_t(-1)).val == 8);
    CHECK(poly_1.eval(num_t()).val == 3);
    CHECK(poly_1.eval(num_t(2)).val == 29);
    CHECK(poly_1.eval(num_t(3)).val == 108);

    CHECK(poly_1.eval(xs) == ys);
    CHECK(poly_t::interp(xs, ys) == poly_1);

    poly_1 = poly_t({num_t(1), num_t(2), num_t(3), num_t(4)});

    xs.assign({num_t(5), num_t(6), num_t(7), num_t(8), num_t(9)});
    ys.assign({num_t(586), num_t(985), num_t(1534), num_t(2257), num_t(3178)});

    CHECK(poly_1.eval(xs) == ys);
    CHECK(poly_t::interp(xs, ys) == poly_1);

    poly_2.resize(4);

    poly_2[3] = num_t(8);

    CHECK(poly_2 == poly_t({num_t(-2), num_t(7), num_t(), num_t(8)}));

    poly_2[0] = num_t();

    CHECK(poly_1.trail() == 0);
    CHECK(poly_2.trail() == 1);

    poly_1.resize(0);

    CHECK(poly_1.is_zero());
    CHECK(!poly_2.is_zero());

    poly_1 = poly_t({num_t(5), num_t(4), num_t(3), num_t(2), num_t(1)});
    poly_2 = poly_t(
        {num_t(598946612), num_t(718735934), num_t(862483121), num_t(635682004), num_t(163871793)}
    );

    CHECK(poly_1.inv(5) == poly_2);
    CHECK(poly_2.inv(5) == poly_1);

    poly_1 = poly_t({num_t(), num_t(1), num_t(2), num_t(3), num_t(4)});
    poly_2 = poly_t({num_t(1), num_t(1), num_t(499122179), num_t(166374064), num_t(291154613)});

    CHECK(poly_1.exp(5) == poly_2);
    CHECK(poly_2.log(5) == poly_1);

    CHECK(poly_t().pow(0, 3) == poly_t({num_t(1)}));
    CHECK(poly_t({num_t(0), num_t(0), num_t(3)}).pow(3, 3) == poly_t());
    CHECK(poly_t({num_t(2), num_t(3)}).pow(2, 4) == poly_t({num_t(4), num_t(12), num_t(9)}));
    CHECK(
        poly_t({num_t(), num_t(3), num_t(1)}).pow(3, 4) == poly_t(
            {num_t(), num_t(), num_t(), num_t(27)}
        )
    );
    CHECK(
        poly_t({num_t(), num_t(3), num_t(1)}).pow(3, 7) == poly_t(
            {num_t(), num_t(), num_t(), num_t(27), num_t(27), num_t(9), num_t(1)}
        )
    );

    std::optional rt = poly_t({num_t(), num_t(), num_t(9), num_t(12)}).sqrt(4);

    CHECK(rt);
    CHECK(*rt == poly_t({num_t(), num_t(3), num_t(2), num_t(332748117)}));

    rt = poly_t({num_t(), num_t(), num_t(10), num_t(12)}).sqrt(4);

    CHECK(!rt);

    rt = poly_t({num_t(), num_t(), num_t(16), num_t(8), num_t(1)}).sqrt(4);

    CHECK(rt);
    CHECK(*rt == poly_t({num_t(), num_t(4), num_t(1)}));

    rt = poly_t({num_t(), num_t(16), num_t(8), num_t(4)}).sqrt(4);

    CHECK(!rt);

    poly_1 = poly_t({num_t(), num_t(-2), num_t(4), num_t(3)});
    poly_2 = poly_t({num_t(-2), num_t(8), num_t(9)});

    CHECK(poly_1.deriv() == poly_2);
    CHECK(poly_2.integ() == poly_1);

    CHECK(poly_1.deriv().integ() == poly_1);
    CHECK(poly_2.integ().deriv() == poly_2);

    poly_1 = poly_t({num_t(-1), num_t(3), num_t(8)});
    poly_2 = poly_t({num_t(), num_t(), num_t(), num_t(-1), num_t(3), num_t(8)});

    CHECK(poly_1.mul_pow(3) == poly_2);
    CHECK(poly_2.div_pow(3) == poly_1);
    CHECK(poly_1.mod_pow(2) == poly_t({num_t(-1), num_t(3)}));
    CHECK(poly_2.mod_pow(2) == poly_t());

    CHECK(poly_1 == poly_t({num_t(-1), num_t(3), num_t(8)}));
    CHECK(poly_1 != poly_t({num_t(1), num_t(3), num_t(8)}));

    poly_1 = poly_t({num_t(), num_t(3), num_t(2)});
    poly_2 = poly_t({num_t(4), num_t(-7)});

    CHECK(poly_1 + poly_2 == poly_t({num_t(4), num_t(-4), num_t(2)}));
    CHECK(poly_1 - poly_2 == poly_t({num_t(-4), num_t(10), num_t(2)}));
    CHECK(poly_1 * poly_t() == poly_t());
    CHECK(poly_1 * poly_2 == poly_3);
    CHECK(poly_3 / poly_1 == poly_2);
    CHECK(poly_3 / poly_2 == poly_1);
    CHECK(poly_3 % poly_1 == poly_t());
    CHECK(poly_2 % poly_1 == poly_2);

    poly_1 = poly_t({num_t(2), num_t(3), num_t(-7)});
    poly_2 = poly_t({num_t(-6), num_t(-9), num_t(21)});

    CHECK(poly_1 * num_t(-3) == poly_2);
    CHECK(poly_2 / num_t(-3) == poly_1);

}
