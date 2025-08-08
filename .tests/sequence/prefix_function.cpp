#include <cstdint>
#include <string>
#include <vector>

#include "include/doctest.h"

#include "sequence/prefix_function.cpp"

TEST_CASE("prefix_function") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abcabcd");

    CHECK(prefix_function(std::begin(str), std::end(str)) == vec_t({0, 0, 0, 1, 2, 3, 0}));

    str.assign("aabaaab");

    CHECK(prefix_function(std::begin(str), std::end(str)) == vec_t({0, 1, 0, 1, 2, 2, 3}));

}
