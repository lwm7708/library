#include <cstdlib>
#include <numeric>

auto pollardRho(long long n) {

    if (n % 2 == 0) {
        return 2ll;
    }

    auto c = 1ll;
    auto gcd = 1ll;

    const auto f = [&](long long x) {
        return static_cast<long long>((__int128_t(x) * x + c) % n);
    };

    while (gcd == 1 || gcd == n) {
        gcd = 1;
        auto ptr_f = f(c);
        auto ptr_s = c;
        while (gcd == 1) {
            gcd = std::gcd(std::abs(ptr_f - ptr_s), n);
            ptr_s = f(ptr_s);
            ptr_f = f(f(ptr_f));
        }
        ++c;
    }

    return gcd;

}
