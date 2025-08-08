#include <cstdint>
#include <string>

#include "include/doctest.h"

#include "math/number_theory/modular_integer.cpp"
#include "sequence/sequence_hasher.cpp"

TEST_CASE("sequence_hasher") {

    static constexpr std::int32_t MOD = 998244353;

    using hshr_t = sequence_hasher<modular_integer<MOD>>;

    hshr_t hshr_1;
    const std::string str("abca");

    hshr_1.push('a');
    hshr_1.push('a');

    CHECK(hshr_1.query(0, 1) == hshr_1.query(1, 2));

    hshr_1.pop();

    hshr_1.push('b');
    hshr_1.push('c');
    hshr_1.push('a');

    CHECK(hshr_1.query(0, 1) != hshr_1.query(1, 2));
    CHECK(hshr_1.query(0, 1) != hshr_1.query(1, 3));
    CHECK(hshr_1.query(0, 1) == hshr_1.query(3, 4));

    const hshr_t hshr_2(std::begin(str), std::end(str));

    CHECK(hshr_1.query(0, 1) != hshr_2.query(1, 2));
    CHECK(hshr_1.query(0, 1) != hshr_2.query(1, 3));
    CHECK(hshr_1.query(0, 1) == hshr_2.query(3, 4));
    CHECK(hshr_1.query(0, 3) == hshr_2.query(0, 3));

    CHECK(hshr_t::hash(std::begin(str), std::end(str)) == hshr_1.query(0, 4));

}
