#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "math/number_theory/miller_rabin.cpp"
#include "math/number_theory/pollard_rho.cpp"
#include "utility/y_combinator.cpp"

std::int32_t primitive_root(std::int64_t mod) {

    using int128_t = __int128_t;

    if (mod == 2) {
        return 1;
    }

    std::vector<std::int64_t> facts;
    std::int32_t rt = 2;

    y_combinator(
        [&](auto self, std::int64_t num) -> void {
            if (num == 1) {
                return;
            }
            if (miller_rabin(num)) {
                facts.push_back(num);
                return;
            }
            const std::int64_t fact = pollard_rho(num);
            self(fact);
            self(num / fact);
        }
    )(mod - 1);

    std::sort(std::begin(facts), std::end(facts));

    facts.erase(std::unique(std::begin(facts), std::end(facts)), std::end(facts));

    while (true) {
        bool valid = true;
        for (auto x : facts) {
            std::int64_t base = rt;
            const auto mul = [&](std::int64_t& a, std::int64_t b) -> void {
                a = (int128_t(a) * b) % mod;
            };
            std::int64_t pow = (mod - 1) / x;
            std::int64_t res = 1;
            while (pow) {
                if (pow & 1) {
                    mul(res, base);
                }
                pow >>= 1;
                mul(base, base);
            }
            if (res == 1) {
                valid = false;
                break;
            }
        }
        if (valid) {
            break;
        }
        ++rt;
    }

    return rt;

}
