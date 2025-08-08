#include <cstdint>
#include <string>
#include <vector>

#include "include/doctest.h"

#include "sequence/z_function.cpp"

TEST_CASE("z_function") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("aaaaa");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 4, 3, 2, 1}));

    str.assign("aaabaab");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 2, 1, 0, 2, 1, 0}));

    str.assign("abacaba");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 0, 1, 0, 3, 0, 1}));

}
