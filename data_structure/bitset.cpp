#include <algorithm>
#include <vector>

class BitSet {

private:

    using BlockT = unsigned long long;

    int blks = 0;
    std::vector<BlockT> data = std::vector<BlockT>();
    BlockT mask = 0;
    int sz = 0;

public:

    class Reference {

    private:

        BlockT& blk;
        BlockT mask = 0;

    public:

        explicit Reference(BlockT& block, int bit) : blk(block), mask(1llu << bit) {}

        operator bool() const {

            return blk & mask;

        }

        auto operator=(bool x) {

            if (!x) {
                blk &= ~mask;
            } else {
                blk |= mask;
            }

        }

    };

    explicit BitSet(
        int sz
    ) : blks((sz + 63) / 64), mask((sz % 64 ? 1llu << sz % 64 : 0) - 1), sz(sz) {

        data.resize(blks);

    }

    auto operator[](int pos) {

        return Reference(data[pos / 64], pos % 64);

    }

    auto operator[](int pos) const {

        return (data[pos / 64] & 1llu << pos % 64) != 0;

    }

    auto operator&=(const BitSet& other) {

        for (auto i = 0; i < blks; ++i) {
            data[i] &= other.data[i];
        }

    }

    auto operator^=(const BitSet& other) {

        for (auto i = 0; i < blks; ++i) {
            data[i] ^= other.data[i];
        }

    }

    auto operator|=(const BitSet& other) {

        for (auto i = 0; i < blks; ++i) {
            data[i] |= other.data[i];
        }

    }

    auto all() const {

        for (auto i = 0; i < blks - 1; ++i) {
            if (~data[i]) {
                return false;
            }
        }

        return (data[blks - 1] & mask) == mask;

    }

    auto any() const {

        for (auto i = 0; i < blks - 1; ++i) {
            if (data[i]) {
                return true;
            }
        }

        return (data[blks - 1] & mask) != 0;

    }

    auto count() const {

        auto bits = __builtin_popcountll(data[blks - 1] & mask);

        for (auto i = 0; i < blks - 1; ++i) {
            bits += __builtin_popcountll(data[i]);
        }

        return bits;

    }

    auto flip() {

        for (auto& x : data) {
            x ^= ~0llu;
        }

    }

    auto reset() {

        std::fill(std::begin(data), std::end(data), 0);

    }

    auto set() {

        std::fill(std::begin(data), std::end(data), ~0llu);

    }

    auto size() const {

        return sz;

    }

    auto operator~() const {

        auto res = *this;

        res.flip();

        return res;

    }

    auto operator<<=(int pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        const auto bits = pos % 64;
        const auto shft = pos / 64;

        for (auto i = blks - 1; i >= shft; --i) {
            data[i] = data[i - shft] << bits;
            if (bits && i > shft) {
                data[i] |= data[i - shft - 1] >> (64 - bits);
            }
        }

        std::fill_n(std::begin(data), shft, 0);

    }

    auto operator>>=(int pos) {

        if (pos >= sz) {
            reset();
            return;
        }

        data[blks - 1] &= mask;

        const auto bits = pos % 64;
        const auto shft = pos / 64;

        for (auto i = 0; i < blks - shft; ++i) {
            data[i] = data[i + shft] >> bits;
            if (bits && i < blks - shft - 1) {
                data[i] |= data[i + shft + 1] << (64 - bits);
            }
        }

        std::fill(std::end(data) - shft, std::end(data), 0);

    }

    auto none() const {

        return !any();

    }

    friend auto operator==(const BitSet& lhs, const BitSet& rhs) {

        if (lhs.sz != rhs.sz) {
            return false;
        }

        const auto& data_1 = lhs.data;
        const auto& data_2 = rhs.data;
        const auto len = lhs.blks;

        for (auto i = 0; i < len - 1; ++i) {
            if (data_1[i] != data_2[i]) {
                return false;
            }
        }

        return ((data_1[len - 1] ^ data_2[len - 1]) & lhs.mask) == 0;

    }

    friend auto operator&(BitSet lhs, const BitSet& rhs) {

        lhs &= rhs;

        return lhs;

    }

    friend auto operator^(BitSet lhs, const BitSet& rhs) {

        lhs ^= rhs;

        return lhs;

    }

    friend auto operator|(BitSet lhs, const BitSet& rhs) {

        lhs |= rhs;

        return lhs;

    }

    friend auto operator<<(BitSet lhs, int pos) {

        lhs <<= pos;

        return lhs;

    }

    friend auto operator>>(BitSet lhs, int pos) {

        lhs >>= pos;

        return lhs;

    }

    friend auto operator!=(const BitSet& lhs, const BitSet& rhs) {

        return !(lhs == rhs);

    }

};
