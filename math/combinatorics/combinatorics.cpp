#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

template <typename T>
class combinatorics {

private:

    std::vector<T> facts;
    std::vector<T> inv_facts;
    std::int32_t nxt;

public:

    explicit combinatorics() : nxt(0) {}

    T comb(std::int32_t n, std::int32_t k) {

        if (n < 0 || k < 0 || n < k) {
            return T();
        }

        reserve(n);

        return facts[n] * inv_facts[k] * inv_facts[n - k];

    }

    T fact(std::int32_t n) {

        if (n < 0) {
            return T();
        }

        reserve(n);

        return facts[n];

    }

    T inv(std::int32_t n) {

        if (n < 0) {
            return T();
        }

        reserve(n);

        return inv_facts[n] * facts[n - 1];

    }

    T inv_fact(std::int32_t n) {

        if (n < 0) {
            return T();
        }

        reserve(n);

        return inv_facts[n];

    }

    void reserve(std::int32_t sz) {

        if (nxt == 0) {
            facts.emplace_back(1);
            inv_facts.emplace_back(1);
            nxt = 1;
        }

        if (sz < nxt) {
            return;
        }

        const std::int32_t cap = std::min(1 << (31 - __builtin_clz(sz * 2 - 1)), T::get_mod() - 1);

        facts.resize(cap + 1);
        inv_facts.resize(cap + 1);

        for (std::int32_t i = nxt; i <= cap; ++i) {
            facts[i] = facts[i - 1] * T(i);
        }

        inv_facts[cap] = T(1) / facts[cap];

        for (std::int32_t i = cap - 1; i >= nxt; --i) {
            inv_facts[i] = inv_facts[i + 1] * T(i + 1);
        }

        nxt = cap + 1;

    }

};
