#include <algorithm>
#include <vector>

template <typename T>
class XorBasis {

public:

    int bits = 0;
    std::vector<T> vecs = std::vector<T>();

    explicit XorBasis(int bits) : bits(bits) {

        vecs.resize(bits);

    }

    auto dim() const {

        return bits - std::count(std::begin(vecs), std::end(vecs), 0);

    }

    auto insert(T vec) {

        for (auto i = bits - 1; vec; --i) {
            if (vec >> i & 1) {
                if (vecs[i] == 0) {
                    vecs[i] = vec;
                }
                vec ^= vecs[i];
            }
        }

    }

    auto query(T vec) const {

        for (auto i = bits - 1; i >= 0 && vec; --i) {
            if (vec >> i & 1) {
                vec ^= vecs[i];
            }
        }

        return vec == 0;

    }

};
