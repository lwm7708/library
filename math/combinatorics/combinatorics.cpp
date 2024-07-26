#include <algorithm>
#include <vector>

template <typename T>
class Combinatorics {

private:

    std::vector<T> facts = std::vector<T>();
    std::vector<T> inv_facts = std::vector<T>();
    int ptr = 0;

public:

    auto reserve(int size) {

        if (ptr == 0) {
            facts.emplace_back(1);
            inv_facts.emplace_back(1);
            ptr = 1;
        }

        if (size < ptr) {
            return;
        }

        const auto sz = std::min(1 << (31 - __builtin_clz(size * 2 - 1)), T::getModulus() - 1);

        facts.resize(sz + 1);
        inv_facts.resize(sz + 1);

        for (auto i = ptr; i <= sz; ++i) {
            facts[i] = facts[i - 1] * T(i);
        }

        inv_facts[sz] = T(1) / facts[sz];

        for (auto i = sz - 1; i >= ptr; --i) {
            inv_facts[i] = inv_facts[i + 1] * T(i + 1);
        }

        ptr = sz + 1;

    }

    auto combine(int n, int k) {

        reserve(n);

        return facts[n] * inv_facts[k] * inv_facts[n - k];

    }

    auto getFact(int n) {

        reserve(n);

        return facts[n];

    }

    auto getInv(int n) {

        reserve(n);

        return inv_facts[n] * facts[n - 1];

    }

    auto getInvFact(int n) {

        reserve(n);

        return inv_facts[n];

    }

    auto permute(int n, int k) {

        reserve(n);

        return facts[n] * inv_facts[n - k];

    }

};
