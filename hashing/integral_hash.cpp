#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

class integral_hash {

private:

    static constexpr std::uint64_t CNST_1 = 0x9e3779b97f4a7c15;
    static constexpr std::uint64_t CNST_2 = 0xbf58476d1ce4e5b9;
    static constexpr std::uint64_t CNST_3 = 0x94d049bb133111eb;

public:

    template <typename T>
    std::size_t operator()(T key) const {

        static const std::uint64_t cnst = (
            std::chrono::steady_clock::now().time_since_epoch().count()
        );

        std::uint64_t res = key;

        res += cnst + CNST_1;

        res = (res ^ (res >> 30)) * CNST_2;
        res = (res ^ (res >> 27)) * CNST_3;

        res ^= res >> 31;

        return std::size_t(res);

    }

};
