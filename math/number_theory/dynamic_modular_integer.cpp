#pragma once

#include <cstdint>

#include "math/number_theory/extended_gcd.cpp"

template <std::int32_t>
class dynamic_modular_integer {

private:

    static inline std::int32_t modulus;

public:

    static std::int32_t get_modulus() {

        return modulus;

    }

    static void set_modulus(std::int32_t mod) {

        modulus = mod;

    }

    std::int32_t val;

    explicit dynamic_modular_integer() : dynamic_modular_integer(0) {}

    explicit dynamic_modular_integer(std::int64_t val) : val(val % get_modulus()) {

        if (this->val < 0) {
            this->val += get_modulus();
        }

    }

    dynamic_modular_integer operator-() const {

        return dynamic_modular_integer(-val);

    }

    void operator++() {

        *this += dynamic_modular_integer(1);

    }

    void operator--() {

        *this -= dynamic_modular_integer(1);

    }

    void operator+=(dynamic_modular_integer other) {

        if (other.val >= get_modulus() - val) {
            val -= get_modulus();
        }

        val += other.val;

    }

    void operator-=(dynamic_modular_integer other) {

        val -= other.val;

        if (val < 0) {
            val += get_modulus();
        }

    }

    void operator*=(dynamic_modular_integer other) {

        val = (std::int64_t(val) * other.val) % get_modulus();

    }

    void operator/=(dynamic_modular_integer other) {

        *this *= dynamic_modular_integer(extended_gcd(other.val, get_modulus())[1]);

    }

    friend dynamic_modular_integer operator+(
        dynamic_modular_integer lhs, dynamic_modular_integer rhs
    ) {

        lhs += rhs;

        return lhs;

    }

    friend dynamic_modular_integer operator-(
        dynamic_modular_integer lhs, dynamic_modular_integer rhs
    ) {

        lhs -= rhs;

        return lhs;

    }

    friend dynamic_modular_integer operator*(
        dynamic_modular_integer lhs, dynamic_modular_integer rhs
    ) {

        lhs *= rhs;

        return lhs;

    }

    friend dynamic_modular_integer operator/(
        dynamic_modular_integer lhs, dynamic_modular_integer rhs
    ) {

        lhs /= rhs;

        return lhs;

    }

};
