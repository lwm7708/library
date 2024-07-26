#include <vector>

template <typename It>
auto prefixFunction(It it_l, It it_r) {

    const auto sz = it_r - it_l;

    auto vals = std::vector<int>(sz);

    for (auto i = 1; i < sz; ++i) {
        auto& len = vals[i];
        const auto& val = it_l[i];
        len = vals[i - 1];
        while (len && val != it_l[len]) {
            len = vals[len - 1];
        }
        len += it_l[len] == val;
    }

    return vals;

}
