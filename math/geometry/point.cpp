#include <cmath>

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
