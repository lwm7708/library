#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <optional>
#include <random>

#include "math/combinatorics/exponentiate.cpp"
#include "math/number_theory/extended_gcd.cpp"

template <std::int32_t>
class dynamic_modular_integer {

private:

    static inline std::int32_t modulus;

public:

    static std::int32_t get_mod() {

        return modulus;

    }

    static void set_mod(std::int32_t mod) {

        modulus = mod;

    }

    std::int32_t val;

    explicit dynamic_modular_integer() : dynamic_modular_integer(0) {}

    explicit dynamic_modular_integer(std::int64_t val) : val(val % get_mod()) {

        if (this->val < 0) {
            this->val += get_mod();
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

        if (other.val >= get_mod() - val) {
            val -= get_mod();
        }

        val += other.val;

    }

    void operator-=(dynamic_modular_integer other) {

        *this += -other;

    }

    void operator*=(dynamic_modular_integer other) {

        val = (std::int64_t(val) * other.val) % get_mod();

    }

    void operator/=(dynamic_modular_integer other) {

        *this *= dynamic_modular_integer(extended_gcd(other.val, get_mod())[1]);

    }

    std::optional<dynamic_modular_integer> sqrt() const {

        using arr_t = std::array<dynamic_modular_integer, 2>;

        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

        if (val <= 1) {
            return std::optional(*this);
        }

        if (exponentiate(*this, (get_mod() - 1) / 2, dynamic_modular_integer(1)).val != 1) {
            return std::nullopt;
        }

        dynamic_modular_integer a;
        std::int32_t pow = (get_mod() + 1) / 2;
        arr_t res({dynamic_modular_integer(1), dynamic_modular_integer()});

        do {
            a = dynamic_modular_integer(rng());
        } while (
            exponentiate(
                a * a - *this, (get_mod() - 1) / 2, dynamic_modular_integer(1)
            ).val != get_mod() - 1
        );

        arr_t base({dynamic_modular_integer(a), dynamic_modular_integer(1)});

        while (pow) {
            const auto mul = [&](const arr_t& num_1, const arr_t& num_2) -> arr_t {
                return arr_t(
                    {
                        num_1[0] * num_2[0] + num_1[1] * num_2[1] * (a * a - *this),
                        num_1[0] * num_2[1] + num_1[1] * num_2[0]
                    }
                );
            };
            if (pow & 1) {
                res = mul(res, base);
            }
            pow >>= 1;
            base = mul(base, base);
        }

        return std::optional(dynamic_modular_integer(std::min(res[0].val, get_mod() - res[0].val)));

    }

    friend bool operator==(dynamic_modular_integer lhs, dynamic_modular_integer rhs) {

        return lhs.val == rhs.val;

    }

    friend bool operator!=(dynamic_modular_integer lhs, dynamic_modular_integer rhs) {

        return !(lhs == rhs);

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
