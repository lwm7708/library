#include <cstdint>

#include "include/doctest.h"

#include "math/algebra/matrix.cpp"
#include "math/combinatorics/exponentiate.cpp"
#include "math/number_theory/modular_integer.cpp"

TEST_CASE("exponentiate") {

    static constexpr std::int32_t MOD = 53;

    using mat_t = matrix<std::int32_t>;

    CHECK(exponentiate(std::int32_t(3), 9) == 19683);
    CHECK(exponentiate(modular_integer<MOD>(7), 123).val == 11);

    mat_t mat(2, 2);

    mat[0][0] = 3;
    mat[0][1] = 8;
    mat[1][0] = 2;
    mat[1][1] = -1;

    mat = exponentiate(mat, 5, mat_t::get_id(2));

    CHECK(mat[0][0] == 3411);
    CHECK(mat[0][1] == 4840);
    CHECK(mat[1][0] == 1210);
    CHECK(mat[1][1] == 991);

}
