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

template <int MOD>
class ModularInteger {

private:

    static constexpr auto MODULUS = MOD;

public:

    static auto getModulus() {

        return MODULUS;

    }

    int val = 0;

    explicit ModularInteger() = default;

    explicit ModularInteger(long long val) : val(val % MODULUS) {

        if (this->val < 0) {
            this->val += MODULUS;
        }

    }

    auto operator-() const {

        return ModularInteger(-val);

    }

    auto operator++() {

        val = val < MODULUS - 1 ? val + 1 : 0;

    }

    auto operator--() {

        val = val ? val - 1 : MODULUS - 1;

    }

    auto operator+=(ModularInteger other) {

        if (other.val >= MODULUS - val) {
            val -= MODULUS;
        }

        val += other.val;

    }

    auto operator-=(ModularInteger other) {

        val -= other.val;

        if (val < 0) {
            val += MODULUS;
        }

    }

    auto operator*=(ModularInteger other) {

        val = static_cast<long long>(val) * other.val % MODULUS;

    }

    auto operator/=(ModularInteger other) {

        *this *= ModularInteger(extendedGCD(other.val, MODULUS)[1]);

    }

    friend auto operator+(ModularInteger lhs, ModularInteger rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(ModularInteger lhs, ModularInteger rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(ModularInteger lhs, ModularInteger rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(ModularInteger lhs, ModularInteger rhs) {

        lhs /= rhs;

        return lhs;

    }

};
