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

template <int>
class DynamicModularInteger {

private:

    static inline auto modulus = 0;

public:

    static auto getModulus() {

        return modulus;

    }

    static auto setModulus(int mod) {

        modulus = mod;

    }

    int val = 0;

    explicit DynamicModularInteger() = default;

    explicit DynamicModularInteger(long long val) : val(val % modulus) {

        if (this->val < 0) {
            this->val += modulus;
        }

    }

    auto operator-() const {

        return DynamicModularInteger(-val);

    }

    auto operator++() {

        val = val < modulus - 1 ? val + 1 : 0;

    }

    auto operator--() {

        val = val ? val - 1 : modulus - 1;

    }

    auto operator+=(DynamicModularInteger other) {

        if (other.val >= modulus - val) {
            val -= modulus;
        }

        val += other.val;

    }

    auto operator-=(DynamicModularInteger other) {

        val -= other.val;

        if (val < 0) {
            val += modulus;
        }

    }

    auto operator*=(DynamicModularInteger other) {

        val = static_cast<long long>(val) * other.val % modulus;

    }

    auto operator/=(DynamicModularInteger other) {

        *this *= DynamicModularInteger(extendedGCD(other.val, modulus)[1]);

    }

    friend auto operator+(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(DynamicModularInteger lhs, DynamicModularInteger rhs) {

        lhs /= rhs;

        return lhs;

    }

};
