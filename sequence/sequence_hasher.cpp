#pragma once

#include <chrono>
#include <cstdint>
#include <vector>

template <typename T>
class sequence_hasher {

private:

    static inline const T base = T(std::chrono::steady_clock::now().time_since_epoch().count());
    static inline std::vector pows = std::vector<T>({T(1)});

    std::vector<T> pfxs;

public:

    template <typename It>
    static std::int32_t hash(It it_l, It it_r) {

        T res;

        while (it_l != it_r) {
            res = res * base + T(*it_l);
            ++it_l;
        }

        return res.val;

    }

    explicit sequence_hasher() : pfxs(1) {}

    template <typename It>
    explicit sequence_hasher(It it_l, It it_r) : sequence_hasher() {

        const std::int32_t len = it_r - it_l;

        while (it_l != it_r) {
            pfxs.push_back(pfxs.back() * base + T(*it_l));
            ++it_l;
        }

        pows.reserve(len + 1);

        while (std::int32_t(std::size(pows)) <= len) {
            pows.push_back(pows.back() * base);
        }

    }

    template <typename U>
    void push(U val) {

        pfxs.push_back(pfxs.back() * base + T(val));

        if (std::size(pows) <= std::size(pfxs)) {
            pows.push_back(pows.back() * base);
        }

    }

    void pop() {

        pfxs.pop_back();

    }

    std::int32_t query(std::int32_t idx_l, std::int32_t idx_r) const {

        return (pfxs[idx_r] - pfxs[idx_l] * (pows[idx_r - idx_l])).val;

    }

};
