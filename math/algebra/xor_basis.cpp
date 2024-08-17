#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

template <typename T>
class xor_basis {

private:

    std::int32_t bits;
    std::vector<T> vecs;

public:

    explicit xor_basis(std::int32_t bits) : bits(bits), vecs(bits) {}

    std::int32_t dim() const {

        return bits - std::count(std::begin(vecs), std::end(vecs), 0);

    }

    void insert(T vec) {

        for (std::int32_t i = bits - 1; vec; --i) {
            if (vec >> i & 1) {
                if (vecs[i] == 0) {
                    vecs[i] = vec;
                }
                vec ^= vecs[i];
            }
        }

    }

    bool query(T vec) const {

        for (std::int32_t i = bits - 1; i >= 0 && vec; --i) {
            if (vec >> i & 1) {
                vec ^= vecs[i];
            }
        }

        return vec == 0;

    }

};
