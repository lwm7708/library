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

template <typename T>
class ModularCongruence {

public:

    T a = T();
    T m = T(1);

    explicit ModularCongruence() = default;

    explicit ModularCongruence(T a, T m) : a(a), m(m) {}

    auto operator&=(ModularCongruence other) {

        const auto [other_a, other_m] = other;

        const auto [div, coef_m, coef_n] = extendedGCD(m, other_m);

        if ((a - other_a) % div) {
            a = 0;
            m = 0;
            return;
        }

        const auto mult = m / div * other_m;

        a = (a + coef_m * (other_a - a) / div % (other_m / div) * m) % mult;
        m = mult;

        if (a < 0) {
            a += m;
        }

    }

    friend auto operator&(ModularCongruence lhs, ModularCongruence rhs) {

        lhs &= rhs;

        return lhs;

    }

};
