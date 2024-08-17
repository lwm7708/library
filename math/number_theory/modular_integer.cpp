#pragma once

#include <cstdint>

#include "math/number_theory/extended_gcd.cpp"

template <std::int32_t MOD>
class modular_integer {

private:

    static constexpr std::int32_t MODULUS = MOD;

public:

    static std::int32_t get_modulus() {

        return MODULUS;

    }

    std::int32_t val;

    explicit modular_integer() : modular_integer(0) {}

    explicit modular_integer(std::int64_t val) : val(val % get_modulus()) {

        if (this->val < 0) {
            this->val += get_modulus();
        }

    }

    modular_integer operator-() const {

        return modular_integer(-val);

    }

    void operator++() {

        *this += modular_integer(1);

    }

    void operator--() {

        *this -= modular_integer(1);

    }

    void operator+=(modular_integer other) {

        if (other.val >= get_modulus() - val) {
            val -= get_modulus();
        }

        val += other.val;

    }

    void operator-=(modular_integer other) {

        val -= other.val;

        if (val < 0) {
            val += get_modulus();
        }

    }

    void operator*=(modular_integer other) {

        val = (std::int64_t(val) * other.val) % get_modulus();

    }

    void operator/=(modular_integer other) {

        *this *= modular_integer(extended_gcd(other.val, get_modulus())[1]);

    }

    friend modular_integer operator+(modular_integer lhs, modular_integer rhs) {

        lhs += rhs;

        return lhs;

    }

    friend modular_integer operator-(modular_integer lhs, modular_integer rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend modular_integer operator*(modular_integer lhs, modular_integer rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend modular_integer operator/(modular_integer lhs, modular_integer rhs) {

        lhs /= rhs;

        return lhs;

    }

};
