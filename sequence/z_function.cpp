#include <algorithm>
#include <vector>

template <typename It>
auto zFunction(It it_l, It it_r) {

    auto ptr_l = 0;
    auto ptr_r = 0;
    const auto sz = it_r - it_l;

    auto vals = std::vector<int>(sz);

    for (auto i = 1; i < sz; ++i) {
        auto& len = vals[i];
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
