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

        const auto [gcd, coef_1, coef_2] = extended_gcd(m, other.m);

        if ((a - other.a) % gcd) {
            m = 0;
            a = 0;
            return;
        }

        const T lcm = m / gcd * other.m;

        a = (a + (((coef_1 * (other.a - a)) / gcd) % (other.m / gcd)) * m) % lcm;
        m = lcm;

        if (a < 0) {
            a += m;
        }

    }

    friend modular_congruence operator&(modular_congruence lhs, modular_congruence rhs) {

        lhs &= rhs;

        return lhs;

    }

};
