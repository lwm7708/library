#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

template <typename It>
auto suffixArray(It it_l, It it_r) {

    auto cnt = 0;
    const auto sz = it_r - it_l;

    auto arr = std::vector<int>(sz);
    auto rnks = std::vector<int>(sz);

    std::iota(std::begin(arr), std::end(arr), 0);

    std::sort(
        std::begin(arr), std::end(arr),
        [&](int idx_1, int idx_2) {
            return it_l[idx_1] < it_l[idx_2];
        }
    );

    for (auto i = 0; i < sz; ++i) {
        cnt += i == 0 || it_l[arr[i - 1]] != it_l[arr[i]];
        rnks[arr[i]] = cnt - 1;
    }

    for (auto i = 1; i < sz && cnt < sz; i *= 2) {
        for (auto& x : arr) {
            x -= i;
            if (x < 0) {
                x += sz;
            }
        }
        auto cnts = std::vector<int>(cnt);
        auto n_arr = std::vector<int>(sz);
        auto n_rnks = std::vector<int>(sz);
        for (auto x : rnks) {
            ++cnts[x];
        }
        std::partial_sum(std::begin(cnts), std::end(cnts), std::begin(cnts));
        for (auto j = sz - 1; j >= 0; --j) {
            auto& c_cnt = cnts[rnks[arr[j]]];
            --c_cnt;
            n_arr[c_cnt] = arr[j];
        }
        cnt = 0;
        for (auto j = 0; j < sz; ++j) {
            const auto norm = [&](int idx) {
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
