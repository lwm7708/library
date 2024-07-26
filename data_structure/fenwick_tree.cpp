namespace FenwickTree {

    template <typename P>
    auto forLvls(int sz, P p) {

        auto idx = 0;

        for (auto i = 31 - __builtin_clz(sz); i >= 0; --i) {
            const auto n_idx = idx | 1 << i;
            if (n_idx <= sz && p(n_idx)) {
                idx = n_idx;
            }
        }

        return idx;

    }

    template <typename F>
    auto forPars(int node, int sz, F f) {

        ++node;

        while (node <= sz) {
            f(node);
            node += node & -node;
        }

    }

    template <typename F>
    auto forRng(int node, F f) {

        while (node) {
            f(node);
            node -= node & -node;
        }

    }

}
