#pragma once

#include <cstdint>
#include <vector>

namespace sieve {

    std::vector<std::int32_t> facts;
    std::vector<std::int32_t> primes;

    void reserve(std::int32_t sz) {

        facts.assign(sz + 1, 0);

        for (std::int32_t i = 2; i <= sz; ++i) {
            if (facts[i] == 0) {
                facts[i] = i;
                primes.push_back(i);
            }
            for (auto x : primes) {
                if (i * x > sz) {
                    break;
                }
                facts[i * x] = x;
                if (x == facts[i]) {
                    break;
                }
            }
        }

    }

}
