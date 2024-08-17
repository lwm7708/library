#pragma once

#include "math/number_theory/extended_gcd.cpp"

template <typename T>
class modular_congruence {

public:

    T m;
    T a;

    explicit modular_congruence() : modular_congruence(0, 0) {}

    explicit modular_congruence(T m, T a) : m(m), a(a) {}

    void operator&=(modular_congruence other) {

        const auto [dvsr, coef_1, coef_2] = extended_gcd(m, other.m);

        if ((a - other.a) % dvsr) {
            m = 0;
            a = 0;
            return;
        }

        const T mult = m / dvsr * other.m;

        a = (a + (((coef_1 * (other.a - a)) / dvsr) % (other.m / dvsr)) * m) % mult;

        m = mult;

        if (a < 0) {
            a += m;
        }

    }

    friend modular_congruence operator&(modular_congruence lhs, modular_congruence rhs) {

        lhs &= rhs;

        return lhs;

    }

};
