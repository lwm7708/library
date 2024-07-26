#include <array>
#include <utility>

template <typename T>
auto extendedGCD(T m, T n) {

    auto a = T(1);
    auto a_in = T();
    auto b = T();
    auto b_in = T(1);

    while (n) {
        const auto q = m / n;
        a_in = std::exchange(a, a_in) - q * a_in;
        b_in = std::exchange(b, b_in) - q * b_in;
        n = std::exchange(m, n) - q * n;
    }

    return std::array<T, 3>({m, a, b});

}
