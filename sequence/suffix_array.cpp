#pragma once

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

template <typename It>
std::vector<std::int32_t> suffix_array(It it_l, It it_r) {

    std::int32_t cnt = 0;
    const std::int32_t sz = it_r - it_l;

    std::vector<std::int32_t> arr(sz);
    std::vector<std::int32_t> rnks(sz);

    std::iota(std::begin(arr), std::end(arr), 0);

    std::sort(
        std::begin(arr), std::end(arr),
        [&](std::int32_t idx_1, std::int32_t idx_2) -> bool {
            return it_l[idx_1] < it_l[idx_2];
        }
    );

    for (std::int32_t i = 0; i < sz; ++i) {
        cnt += i == 0 || it_l[arr[i - 1]] != it_l[arr[i]];
        rnks[arr[i]] = cnt - 1;
    }

    for (std::int32_t i = 1; i < sz && cnt < sz; i *= 2) {
        for (auto& x : arr) {
            x -= i;
            if (x < 0) {
                x += sz;
            }
        }
        std::vector<std::int32_t> idxs(cnt);
        std::vector<std::int32_t> n_arr(sz);
        std::vector<std::int32_t> n_rnks(sz);
        for (auto x : rnks) {
            ++idxs[x];
        }
        std::partial_sum(std::begin(idxs), std::end(idxs), std::begin(idxs));
        for (std::int32_t j = sz - 1; j >= 0; --j) {
            std::int32_t& idx = idxs[rnks[arr[j]]];
            --idx;
            n_arr[idx] = arr[j];
        }
        cnt = 0;
        for (std::int32_t j = 0; j < sz; ++j) {
            const auto norm = [&](std::int32_t idx) -> std::int32_t {
                return idx < sz ? idx : idx - sz;
            };
            cnt += (
                j == 0 || rnks[n_arr[j - 1]] != rnks[n_arr[j]] ||
                rnks[norm(n_arr[j - 1] + i)] != rnks[norm(n_arr[j] + i)]
            );
            n_rnks[n_arr[j]] = cnt - 1;
        }
        arr = std::move(n_arr);
        rnks = std::move(n_rnks);
    }

    return arr;

}
