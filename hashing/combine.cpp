#include <cstddef>

auto combineHash(std::size_t hash, std::size_t seed) {

    static constexpr auto CNST = 0x9e3779b9;

    seed ^= hash + CNST + (seed << 6) + (seed >> 2);

    return seed;

}
