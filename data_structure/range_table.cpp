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
    auto forRng(int idx_l, int idx_r, F f) {

        --idx_r;

        if (idx_l == idx_r) {
            f(0, idx_l);
            return;
        }

        const auto lvl = log2(idx_l ^ idx_r) + 1;

        f(lvl, idx_l);
        f(lvl, idx_r);

    }

}
