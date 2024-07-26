#include <initializer_list>

template <typename T>
auto checkBases(T n, const std::initializer_list<int>& bases) {

    if (n < 2) {
        return false;
    }

    const auto s = __builtin_ctzll(n - 1);

    for (auto x : bases) {
        if (n == x) {
            return true;
        }
        auto base = T(x);
        auto d = (n - 1) >> s;
        auto f = T(1);
        const auto mul = [&](T& a, T b) {
            a = __int128(a) * b % n;
        };
        while (d) {
            if (d & 1) {
                mul(f, base);
            }
            mul(base, base);
            d >>= 1;
        }
        auto valid = f == 1;
        for (auto i = 0; i < s && !valid; ++i) {
            valid = f == n - 1;
            mul(f, f);
        }
        if (!valid) {
            return false;
        }
    }

    return true;

}

auto millerRabin(int n) {

    return checkBases(n, {2, 3, 5, 7});

}

auto millerRabin(long long n) {

    return checkBases(n, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37});

}
