#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "math/algebra/fast_fourier_transform.cpp"
#include "math/number_theory/modular_integer.cpp"

TEST_CASE("fast_fourier_transform") {

    static constexpr std::int32_t MOD = 998244353;

    using num_t = modular_integer<MOD>;

    std::vector poly({num_t(3), num_t(7), num_t(4), num_t(2)});
    const std::vector rts({num_t(1), num_t(998244352), num_t(911660635), num_t(372528824)});

    poly = fast_fourier_transform(poly, 0, rts);

    CHECK(poly == std::vector({num_t(16), num_t(565325762), num_t(998244351), num_t(432918589)}));

    poly = fast_fourier_transform(poly, 1, rts);

    CHECK(poly == std::vector({num_t(3), num_t(7), num_t(4), num_t(2)}));

    poly.assign({num_t(4), num_t(-2), num_t(3), num_t(), num_t(), num_t(), num_t(), num_t()});

    poly = fast_fourier_transform(poly, 0, rts);

    for (std::int32_t i = 0; i < 8; ++i) {
        poly[i] = poly[i] * poly[i];
    }

    poly = fast_fourier_transform(poly, 1, rts);

    CHECK(
        poly == std::vector(
            {num_t(16), num_t(-16), num_t(28), num_t(-12), num_t(9), num_t(), num_t(), num_t()}
        )
    );

}
