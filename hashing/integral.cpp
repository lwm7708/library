#include <chrono>
#include <cstddef>

class IntegralHash {

private:

    static constexpr auto CNST_1 = 0x9e3779b97f4a7c15ll;
    static constexpr auto CNST_2 = 0xbf58476d1ce4e5b9ll;
    static constexpr auto CNST_3 = 0x94d049bb133111ebll;

public:

    template <typename T>
    auto operator()(T key) const {

        static const auto cnst = static_cast<unsigned long long>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );

        auto res = static_cast<unsigned long long>(key);

        res += cnst + CNST_1;
        res = (res ^ (res >> 30)) * CNST_2;
        res = (res ^ (res >> 27)) * CNST_3;
        res ^= res >> 31;

        return static_cast<std::size_t>(res);

    }

};
