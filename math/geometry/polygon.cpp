#pragma once

#include <cstdint>
#include <vector>

#include "math/geometry/point.cpp"
#include "math/geometry/segment.cpp"

template <typename T>
class polygon {

private:

    using pt_t = point<T>;
    using seg_t = segment<T>;

    std::int32_t sz;
    std::vector<pt_t> vtxs;

public:

    explicit polygon() : polygon(0) {}

    explicit polygon(std::int32_t sz) : sz(sz), vtxs(sz) {}

    template <typename It>
    explicit polygon(It it_l, It it_r) : sz(it_r - it_l), vtxs(it_l, it_r) {}

    pt_t& operator[](std::int32_t pos) {

        return vtxs[pos];

    }

    const pt_t& operator[](std::int32_t pos) const {

        return vtxs[pos];

    }

    T area() const {

        T res = 0;

        for (std::int32_t i = 0; i < sz; ++i) {
            res += pt_t::cross(vtxs[i], vtxs[i < sz - 1 ? i + 1 : 0]);
        }

        res = std::abs(res);

        return res;

    }

    double perim() const {

        double res = 0;

        for (std::int32_t i = 0; i < sz; ++i) {
            res += seg_t(vtxs[i], vtxs[i < sz - 1 ? i + 1 : 0]).length();
        }

        return res;

    }

    std::int32_t contains(pt_t pt) const {

        std::int32_t res = 0;
        const auto [x, y] = pt;

        for (std::int32_t i = 0; i < sz; ++i) {
            const pt_t a = vtxs[i];
            const pt_t b = vtxs[i < sz - 1 ? i + 1 : 0];
            if (seg_t(a, b).contains(pt)) {
                return 2;
            }
            res ^= (
                a.x < x && x <= b.x && pt_t::cross(a - b, pt - b) > 0
            ) || (b.x < x && x <= a.x && pt_t::cross(b - a, pt - a) > 0);
        }

        return res;

    }

    std::int32_t size() const {

        return sz;

    }

    auto begin() {

        return std::begin(vtxs);

    }

    auto begin() const {

        return std::begin(vtxs);

    }

    auto end() {

        return std::end(vtxs);

    }

    auto end() const {

        return std::end(vtxs);

    }

};
