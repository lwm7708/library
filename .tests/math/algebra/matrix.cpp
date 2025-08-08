#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "math/algebra/matrix.cpp"

TEST_CASE("matrix") {

    using mat_t = matrix<std::int32_t>;
    using vec_t = std::vector<std::int32_t>;

    mat_t mat_1(2, 2);
    mat_t mat_2(2, 3);
    mat_t mat_3(2, 3);
    std::int32_t sum = 0;

    mat_1[0][1] = 3;
    mat_1[1][0] = 1;
    mat_1[1][1] = 2;

    mat_2[0] = vec_t({-3, 2, 5});
    mat_2[1] = vec_t({3, 8, -9});
    mat_3[0] = vec_t({9, 24, -27});
    mat_3[1] = vec_t({0, 20, -8});

    CHECK(mat_1[0] == vec_t({0, 3}));
    CHECK(mat_1[1] == vec_t({1, 2}));

    vec_t& vec = mat_1[1];

    vec[0] = 2;

    CHECK(mat_1[0] == vec_t({0, 3}));
    CHECK(mat_1[1] == vec_t({2, 2}));

    mat_1 *= mat_2;

    CHECK(mat_1 == mat_3);
    CHECK(mat_1 != mat_2);

    mat_1 *= -2;

    CHECK(mat_1[0][1] == -48);
    CHECK(mat_1[1][2] == 16);

    mat_1 = mat_t(2, 2);

    mat_1[0] = vec_t({0, 3});
    mat_1[1] = vec_t({2, 2});

    CHECK(mat_1 * mat_2 == mat_3);

    mat_2 = mat_t(2, 2);

    mat_2[0] = vec_t({0, -9});
    mat_2[1] = vec_t({-6, -6});

    CHECK(mat_1 * -3 == mat_2);

    for (const auto& x : mat_1) {
        for (auto y : x) {
            sum += y;
        }
    }

    CHECK(sum == 7);

}
