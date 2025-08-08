#include <cstdint>
#include <vector>

#include "include/doctest.h"

#include "graph/centroid_decomposition.cpp"

TEST_CASE("centroid_decomposition") {

    using vec_t = std::vector<std::int32_t>;

    CHECK(centroid_decomposition(vec_t({0, 1}), vec_t({1, 2})) == vec_t({1, -1, 1}));
    CHECK(
        centroid_decomposition(vec_t({0, 0, 1, 3, 3}), vec_t({1, 3, 2, 4, 5})) == vec_t(
            {-1, 0, 1, 0, 3, 3}
        )
    );

}
