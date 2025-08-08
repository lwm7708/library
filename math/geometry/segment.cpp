#pragma once

#include <algorithm>
#include <cstdint>

#include "math/geometry/point.cpp"

template <typename T>
class segment {

private:

    using pt_t = point<T>;

public:

    static bool intersects(const segment& seg_1, const segment& seg_2) {

        const auto sign = [](pt_t vec_1, pt_t vec_2) -> std::int32_t {
            const T prod = pt_t::cross(vec_1, vec_2);
            if (prod == 0) {
                return 0;
            }
            return prod < 0 ? -1 : 1;
        };

        const std::int32_t sgn_1 = sign(seg_1.b - seg_1.a, seg_2.a - seg_1.a);
        const std::int32_t sgn_2 = sign(seg_1.b - seg_1.a, seg_2.b - seg_1.a);

        if (sgn_1 == 0 && sgn_2 == 0) {
            const auto isects = [](T l_1, T r_1, T l_2, T r_2) -> bool {
                if (l_1 > r_1) {
                    std::swap(l_1, r_1);
                }
                if (l_2 > r_2) {
                    std::swap(l_2, r_2);
                }
                return std::max(l_1, l_2) <= std::min(r_1, r_2);
            };
            return isects(seg_1.a.x, seg_1.b.x, seg_2.a.x, seg_2.b.x) && isects(
                seg_1.a.y, seg_1.b.y, seg_2.a.y, seg_2.b.y
            );
        }

        const pt_t vec = seg_2.b - seg_2.a;

        return sgn_1 != sgn_2 && sign(vec, seg_1.a - seg_2.a) != sign(vec, seg_1.b - seg_2.a);

    }

    pt_t a;
    pt_t b;

    explicit segment() : segment(pt_t(), pt_t()) {}

    explicit segment(pt_t a, pt_t b) : a(a), b(b) {}

    double length() const {

        return (b - a).length();

    }

    T norm() const {

        return (b - a).norm();

    }

    bool contains(pt_t pt) const {

        const auto [mn_x, mx_x] = std::minmax(a.x, b.x);
        const auto [mn_y, mx_y] = std::minmax(a.y, b.y);
        const auto [x, y] = pt;

        return pt_t::cross(b - a, pt - a) == 0 && x >= mn_x && x <= mx_x && y >= mn_y && y <= mx_y;

    }

};
