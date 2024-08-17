#pragma once

#include <cstdint>
#include <vector>

template <typename It>
std::vector<std::int32_t> prefix_function(It it_l, It it_r) {

    const std::int32_t sz = it_r - it_l;

    std::vector<std::int32_t> vals(sz);

    for (std::int32_t i = 1; i < sz; ++i) {
        std::int32_t& len = vals[i];
        const auto val = it_l[i];
        len = vals[i - 1];
        while (len && val != it_l[len]) {
            len = vals[len - 1];
        }
        len += it_l[len] == val;
    }

    return vals;

}
