#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

template <typename It>
std::vector<std::int32_t> manacher(It it_l, It it_r) {

    std::int32_t ptr_l = 0;
    std::int32_t ptr_r = 0;
    const std::int32_t sz = it_r - it_l;

    std::vector<std::int32_t> lens(sz);

    for (std::int32_t i = 0; i < sz; ++i) {
        if (i < ptr_r) {
            lens[i] = std::min(lens[ptr_l + ptr_r - i], ptr_r - i);
        }
        while (i - lens[i] >= 0 && i + lens[i] < sz && it_l[i - lens[i]] == it_l[i + lens[i]]) {
            ++lens[i];
        }
        if (i + lens[i] > ptr_r) {
            ptr_l = i - lens[i];
            ptr_r = i + lens[i];
        }
    }

    return lens;

}
