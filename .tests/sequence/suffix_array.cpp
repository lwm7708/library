#include <cstdint>
#include <string>
#include <vector>

#include "include/doctest.h"

#include "sequence/suffix_array.cpp"

TEST_CASE("suffix_array") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abaab ");

    CHECK(suffix_array(std::begin(str), std::end(str)) == vec_t({5, 2, 3, 0, 4, 1}));

    str.assign("dcafac ");

    CHECK(suffix_array(std::begin(str), std::end(str)) == vec_t({6, 4, 2, 5, 1, 0, 3}));

}
