#pragma once

#include <cstdint>
#include <vector>

template <typename It>
std::vector<std::int32_t> kasai(It it, const std::vector<std::int32_t>& arr) {

    std::int32_t len = 0;
    const std::int32_t sz = std::size(arr);

    std::vector<std::int32_t> lens(sz - 1);
    std::vector<std::int32_t> rnks(sz);

    for (std::int32_t i = 0; i < sz; ++i) {
        rnks[arr[i]] = i;
    }

    for (std::int32_t i = 0; i < sz; ++i) {
        if (rnks[i] == sz - 1) {
            len = 0;
            continue;
        }
        const std::int32_t idx = arr[rnks[i] + 1];
        while (i + len < sz && idx + len < sz && it[i + len] == it[idx + len]) {
            ++len;
        }
        lens[rnks[i]] = len;
        len -= len > 0;
    }

    return lens;

}
