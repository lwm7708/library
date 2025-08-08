#include <cstdint>
#include <string>
#include <vector>

#include "include/doctest.h"

#include "sequence/kasai.cpp"

TEST_CASE("kasai") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abaab ");

    CHECK(kasai(std::begin(str), vec_t({5, 2, 3, 0, 4, 1})) == vec_t({0, 1, 2, 0, 1}));

    str.assign("dcafac ");

    CHECK(kasai(std::begin(str), vec_t({6, 4, 2, 5, 1, 0, 3})) == vec_t({0, 1, 0, 1, 0, 0}));

}
