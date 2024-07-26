#include <algorithm>
#include <array>
#include <cstdlib>
#include <utility>

template <typename T>
auto boundDiophantine(T x, T y, T shft_x, T shft_y, T mn_x, T mx_x, T mn_y, T mx_y) {

    const auto shift = [&](T amount) {
        x += shft_x * amount;
        y -= shft_y * amount;
    };

    shift((mn_x - x) / shft_x);

    const auto emp_rng = std::array<T, 3>();
    const auto sign_a = shft_x > 0 ? 1 : -1;
    const auto sign_b = shft_y > 0 ? 1 : -1;

    if (x < mn_x) {
        shift(sign_a);
    }

    if (x > mx_x) {
        return emp_rng;
    }

    const auto x_1 = x;

    shift((mx_x - x) / shft_x);

    if (x > mx_x) {
        shift(-sign_a);
    }

    const auto x_2 = x;

    shift((y - mn_y) / shft_y);

    if (y < mn_y) {
        shift(-sign_b);
    }

    if (y > mx_y) {
        return emp_rng;
    }

    auto x_3 = x;

    shift((y - mx_y) / shft_y);

    if (y > mx_y) {
        shift(sign_b);
    }

    if (x_3 > x) {
        std::swap(x_3, x);
    }

    const auto x_hi = std::min(x_2, x);
    const auto x_lo = std::max(x_1, x_3);

    if (x_lo > x_hi) {
        return emp_rng;
    }

    return std::array<T, 3>({x_lo, x_hi, (x_hi - x_lo) / std::abs(shft_x) + 1});

}

template <typename T>
auto extendedGCD(T m, T n) {

    auto a = T(1);
    auto a_in = T();
    auto b = T();
    auto b_in = T(1);

    while (n) {
        const auto q = m / n;
        a_in = std::exchange(a, a_in) - q * a_in;
        b_in = std::exchange(b, b_in) - q * b_in;
        n = std::exchange(m, n) - q * n;
    }

    return std::array<T, 3>({m, a, b});

}

template <typename T>
auto diophantine(T a, T b, T c) {

    if (a == 0 && b == 0) {
        return std::array<T, 3>({0, 0, c == 0 ? 3 : 0});
    }

    auto [div, x, y] = extendedGCD(std::abs(a), std::abs(b));

    if (c % div) {
        return std::array<T, 3>();
    }

    x *= c / div;
    y *= c / div;

    if (a < 0) {
        x = -x;
    }

    if (b < 0) {
        y = -y;
    }

    return std::array<T, 3>({x, y, a && b ? 1 : 2});

}
