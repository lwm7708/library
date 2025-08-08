#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

class bitset {

private:

    using blk_t = std::uint64_t;

    std::int32_t sz;
    std::int32_t blks;
    blk_t mask;

public:

    class reference {

    private:

        blk_t& blk;
        blk_t mask;

    public:

        explicit reference(blk_t& blk, std::int32_t bit) : blk(blk), mask(blk_t(1) << bit) {}

        operator bool() const {

            return (blk & mask) != 0;

        }

        void operator=(bool x) {

            if (!x) {
                blk &= ~mask;
            } else {
                blk |= mask;
            }

        }

    };

    std::vector<blk_t> data;

    explicit bitset() : bitset(0) {}

    explicit bitset(
        std::int32_t sz
    ) : sz(sz), blks((sz + 63) / 64), mask((sz % 64 ? blk_t(1) << (sz % 64) : 0) - 1), data(blks) {}

    reference operator[](std::int32_t pos) {

        return reference(data[pos / 64], pos % 64);

    }

    bool operator[](std::int32_t pos) const {

        return data[pos / 64] >> (pos % 64) & 1;

    }

    bitset operator~() const {

        bitset res = *this;

        res.flip();

        return res;

    }

    void operator&=(const bitset& other) {

        for (std::int32_t i = 0; i < blks; ++i) {
            data[i] &= other.data[i];
        }

    }

    void operator|=(const bitset& other) {

        for (std::int32_t i = 0; i < blks; ++i) {
            data[i] |= other.data[i];
        }

    }

    void operator^=(const bitset& other) {

        for (std::int32_t i = 0; i < blks; ++i) {
            data[i] ^= other.data[i];
        }

    }

    void operator<<=(std::int32_t pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        const std::int32_t bits = pos % 64;
        const std::int32_t shft = pos / 64;

        for (std::int32_t i = blks - 1; i >= shft; --i) {
            data[i] = data[i - shft] << bits;
            if (bits && i > shft) {
                data[i] |= data[i - shft - 1] >> (64 - bits);
            }
        }

        std::fill_n(std::begin(data), shft, 0);

    }

    void operator>>=(std::int32_t pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        data[blks - 1] &= mask;

        const std::int32_t bits = pos % 64;
        const std::int32_t shft = pos / 64;

        for (std::int32_t i = 0; i < blks - shft; ++i) {
            data[i] = data[i + shft] >> bits;
            if (bits && i < blks - shft - 1) {
                data[i] |= data[i + shft + 1] << (64 - bits);
            }
        }

        std::fill(std::end(data) - shft, std::end(data), 0);

    }

    bool all() const {

        for (std::int32_t i = 0; i < blks - 1; ++i) {
            if (~data[i]) {
                return false;
            }
        }

        return (data[blks - 1] & mask) == mask;

    }

    bool any() const {

        for (std::int32_t i = 0; i < blks - 1; ++i) {
            if (data[i]) {
                return true;
            }
        }

        return (data[blks - 1] & mask) != 0;

    }

    bool none() const {

        return !any();

    }

    std::int32_t count() const {

        std::int32_t bits = __builtin_popcountll(data[blks - 1] & mask);

        for (std::int32_t i = 0; i < blks - 1; ++i) {
            bits += __builtin_popcountll(data[i]);
        }

        return bits;

    }

    void reset() {

        std::fill_n(std::begin(data), blks, 0);

    }

    void set() {

        std::fill_n(std::begin(data), blks, ~blk_t());

    }

    void flip() {

        for (auto& x : data) {
            x ^= ~blk_t();
        }

    }

    std::int32_t size() const {

        return sz;

    }

    friend bool operator==(const bitset& lhs, const bitset& rhs) {

        if (lhs.sz != rhs.sz) {
            return false;
        }

        const std::int32_t len = lhs.blks;

        if (len == 0) {
            return true;
        }

        const std::vector<blk_t>& data_l = lhs.data;
        const std::vector<blk_t>& data_r = rhs.data;

        return std::equal(std::begin(data_l), std::begin(data_l) + len - 1, std::begin(data_r)) && (
            (data_l[len - 1] ^ data_r[len - 1]) & lhs.mask
        ) == 0;

    }

    friend bool operator!=(const bitset& lhs, const bitset& rhs) {

        return !(lhs == rhs);

    }

    friend bitset operator&(bitset lhs, const bitset& rhs) {

        lhs &= rhs;

        return lhs;

    }

    friend bitset operator|(bitset lhs, const bitset& rhs) {

        lhs |= rhs;

        return lhs;

    }

    friend bitset operator^(bitset lhs, const bitset& rhs) {

        lhs ^= rhs;

        return lhs;

    }

    friend bitset operator<<(bitset lhs, std::int32_t pos) {

        lhs <<= pos;

        return lhs;

    }

    friend bitset operator>>(bitset lhs, std::int32_t pos) {

        lhs >>= pos;

        return lhs;

    }

};
