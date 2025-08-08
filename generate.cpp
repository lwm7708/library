#include <chrono>
#include <cstdint>
#include <random>

namespace generate {

    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    template <typename T>
    T next_int(T a, T b) {

        return std::uniform_int_distribution<T>(a, b - 1)(rng);

    }

    template <typename T>
    T next_real(T a, T b) {

        return std::uniform_real_distribution<T>(a, b)(rng);

    }

    bool next_bool() {

        return next_int<std::int32_t>(0, 2) == 1;

    }

}
