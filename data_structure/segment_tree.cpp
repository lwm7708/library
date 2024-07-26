namespace SegmentTree {

    template <typename P>
    auto forLvls(int node, int sz, bool dir, P p) {

        while (node < sz) {
            node = node << 1 | dir + (!dir ? p(node) : -p(node));
        }

        return node;

    }

    template <typename F>
    auto forRng(int node_1, int node_2, F f) {

        while (node_1 < node_2) {
            if (node_1 & 1) {
                f(node_1);
                ++node_1;
            }
            if (node_2 & 1) {
                --node_2;
                f(node_2);
            }
            node_1 >>= 1;
            node_2 >>= 1;
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
    auto forRngOrd(int node_1, int node_2, bool dir, F f) {

        auto base = !dir ? node_1 - 1 : node_2;
        const auto mask = (1 << log2((node_1 - 1) ^ node_2)) - 1;
        const auto offset = !dir ? 1 : -1;

        auto node = (!dir ? -node_1 : node_2) & mask;

        while (node) {
            const auto bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }

        base = dir ? node_1 - 1 : node_2;
        node = (dir ? -node_1 : node_2) & mask;

        while (node) {
            const auto bit = log2(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }

    }

}
