namespace SegmentTree {

    template <typename P>
    auto forLvls(int node, int sz, bool dir, P p) {

        while (node < sz) {
            node = node << 1 | dir + (!dir ? p(node) : -p(node));
        }

        return node;

    }

    template <typename F>
    auto forRng(int node_l, int node_r, F f) {

        while (node_l < node_r) {
            if (node_l & 1) {
                f(node_l);
                ++node_l;
            }
            if (node_r & 1) {
                --node_r;
                f(node_r);
            }
            node_l >>= 1;
            node_r >>= 1;
        }

    }

    auto log2(int x) {

        return 31 - __builtin_clz(x);

    }

    template <typename F>
    auto forPars(int node, bool dir, F f) {

        const auto lvls = log2(node);

        for (auto i = 1; i <= lvls; ++i) {
            f(node >> (!dir ? lvls - i + 1 : i));
        }

    }

    template <typename F>
    auto forRngOrd(int node_l, int node_r, bool dir, F f) {

        auto base = !dir ? node_l - 1 : node_r;
        const auto mask = (1 << log2((node_l - 1) ^ node_r)) - 1;
        const auto offset = !dir ? 1 : -1;

        auto node = (!dir ? -node_l : node_r) & mask;

        while (node) {
            const auto bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }

        base = dir ? node_l - 1 : node_r;
        node = (dir ? -node_l : node_r) & mask;

        while (node) {
            const auto bit = log2(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }

    }

}
