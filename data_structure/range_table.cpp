namespace RangeTable {

    auto log2(int x) {

        return 31 - __builtin_clz(x);

    }

    template <typename F>
    auto forAll(int sz, F f) {

        for (auto i = 0; i < sz; ++i) {
            f(0, i, true);
        }

        for (auto i = 1; i <= log2(sz); ++i) {
            const auto lvl_sz = 1 << (i - 1);
            for (auto j = 0; j < sz >> i; ++j) {
                for (auto k = 1; k <= lvl_sz; ++k) {
                    f(i, lvl_sz * (j << 1 | 1) - k, k == 1);
                }
                for (auto k = 0; k < lvl_sz; ++k) {
                    f(i, lvl_sz * (j << 1 | 1) + k, k == 0);
                }
            }
        }

    }

    template <typename F>
    auto forRng(int idx_1, int idx_2, F f) {

        --idx_2;

        if (idx_1 == idx_2) {
            f(0, idx_1);
            return;
        }

        const auto lvl = log2(idx_1 ^ idx_2) + 1;

        f(lvl, idx_1);
        f(lvl, idx_2);

    }

}
