#include <algorithm>
#include <vector>

template <typename It>
auto manacher(It it_l, It it_r) {

    auto ptr_l = 0;
    auto ptr_r = 0;
    const auto sz = it_r - it_l;

    auto lens = std::vector<int>(sz);

    for (auto i = 0; i < sz; ++i) {
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
