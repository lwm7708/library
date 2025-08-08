#pragma once

#include <cmath>

template <typename T>
class point {

public:

    static T cross(point a, point b) {

        return a.x * b.y - a.y * b.x;

    }

    static T dot(point a, point b) {

        return a.x * b.x + a.y * b.y;

    }

    T x;
    T y;

    explicit point() : point(0, 0) {}

    explicit point(T x, T y) : x(x), y(y) {}

    point operator-() const {

        return point(-x, -y);

    }

    void operator+=(point other) {

        x += other.x;
        y += other.y;

    }

    void operator-=(point other) {

        x -= other.x;
        y -= other.y;

    }

    void operator*=(T fact) {

        x *= fact;
        y *= fact;

    }

    void operator/=(T dvsr) {

        x /= dvsr;
        y /= dvsr;

    }

    double length() const {

        return std::sqrt(norm());

    }

    T norm() const {

        return dot(*this, *this);

    }

    friend bool operator==(point lhs, point rhs) {

        return lhs.x == rhs.x && lhs.y == rhs.y;

    }

    friend bool operator!=(point lhs, point rhs) {

        return !(lhs == rhs);

    }

    friend point operator+(point lhs, point rhs) {

        lhs += rhs;

        return lhs;

    }

    friend point operator-(point lhs, point rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend point operator*(point lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend point operator/(point lhs, T rhs) {

        lhs /= rhs;

        return lhs;

    }

};
