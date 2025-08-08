#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

template <typename It>
std::vector<std::int32_t> z_function(It it_l, It it_r) {

    std::int32_t ptr_l = 0;
    std::int32_t ptr_r = 0;
    const std::int32_t sz = it_r - it_l;

    std::vector<std::int32_t> vals(sz);

    for (std::int32_t i = 1; i < sz; ++i) {
        std::int32_t& len = vals[i];
        if (i < ptr_r) {
            len = std::min(vals[i - ptr_l], ptr_r - i);
        }
        while (len < sz - i && it_l[i + len] == it_l[len]) {
            ++len;
        }
        if (i + len > ptr_r) {
            ptr_l = i;
            ptr_r = i + len;
        }
    }

    return vals;

}
