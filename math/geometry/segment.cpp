#include <algorithm>
#include <cmath>
#include <utility>

template <typename T>
class Point {

public:

    static auto cross(Point a, Point b) {

        return a.x * b.y - a.y * b.x;

    }

    static auto dot(Point a, Point b) {

        return a.x * b.x + a.y * b.y;

    }

    T x = T();
    T y = T();

    explicit Point() = default;

    explicit Point(T x, T y) : x(x), y(y) {}

    auto operator-() const {

        return Point(-x, -y);

    }

    auto operator+=(Point other) {

        x += other.x;
        y += other.y;

    }

    auto operator-=(Point other) {

        x -= other.x;
        y -= other.y;

    }

    auto operator*=(T fact) {

        x *= fact;
        y *= fact;

    }

    auto operator/=(T div) {

        x /= div;
        y /= div;

    }

    auto norm() const {

        return Point::dot(*this, *this);

    }

    auto length() const {

        return std::hypot(x, y);

    }

    auto quadrant() const {

        if (y == 0) {
            if (x == 0) {
                return 0;
            }
            return x > 0 ? 1 : 3;
        }

        if (y > 0) {
            return x > 0 ? 1 : 2;
        }

        return x < 0 ? 3 : 4;

    }

    friend auto operator==(Point lhs, Point rhs) {

        return lhs.x == rhs.x && lhs.y == rhs.y;

    }

    friend auto operator+(Point lhs, Point rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(Point lhs, Point rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(Point lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(Point lhs, T rhs) {

        lhs /= rhs;

        return lhs;

    }

    friend auto operator*(T lhs, Point rhs) {

        return rhs * lhs;

    }

};

template <typename T>
class Segment {

private:

    using PointT = Point<T>;

public:

    static auto intersects(const Segment& s_1, const Segment& s_2) {

        const auto sign = [](PointT v_1, PointT v_2) {
            const auto prod = PointT::cross(v_1, v_2);
            if (prod == 0) {
                return 0;
            }
            return prod > 0 ? 1 : -1;
        };

        const auto sign_1 = sign(s_1.b - s_1.a, s_2.a - s_1.a);
        const auto sign_2 = sign(s_1.b - s_1.a, s_2.b - s_1.a);

        if (sign_1 == 0 && sign_2 == 0) {
            const auto isects = [](T a_1, T a_2, T b_1, T b_2) {
                if (a_1 > a_2) {
                    std::swap(a_1, a_2);
                }
                if (b_1 > b_2) {
                    std::swap(b_1, b_2);
                }
                return std::max(a_1, b_1) <= std::min(a_2, b_2);
            };
            return (
                isects(s_1.a.x, s_1.b.x, s_2.a.x, s_2.b.x) &&
                isects(s_1.a.y, s_1.b.y, s_2.a.y, s_2.b.y)
            );
        }

        const auto vec = s_2.b - s_2.a;

        return sign_1 != sign_2 && sign(vec, s_1.a - s_2.a) != sign(vec, s_1.b - s_2.a);

    }

    PointT a = PointT();
    PointT b = PointT();

    explicit Segment() = default;

    explicit Segment(PointT a, PointT b) : a(a), b(b) {}

    auto contains(PointT p) const {

        const auto [mn_x, mx_x] = std::minmax(a.x, b.x);
        const auto [mn_y, mx_y] = std::minmax(a.y, b.y);

        return (
            PointT::cross(b - a, p - a) == 0 && p.x >= mn_x && p.x <= mx_x && p.y >= mn_y &&
            p.y <= mx_y
        );

    }

    auto length() const {

        return (b - a).length();

    }

    auto norm() const {

        return (b - a).norm();

    }

};
