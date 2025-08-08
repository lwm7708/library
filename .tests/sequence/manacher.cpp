#include <cstdint>
#include <string>
#include <vector>

#include "include/doctest.h"

#include "sequence/manacher.cpp"

TEST_CASE("manacher") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abcba");

    CHECK(manacher(std::begin(str), std::end(str)) == vec_t({1, 1, 3, 1, 1}));

    str.assign("abbbcbbcaaac");

    CHECK(manacher(std::begin(str), std::end(str)) == vec_t({1, 1, 2, 1, 3, 1, 1, 1, 1, 3, 1, 1}));

}
