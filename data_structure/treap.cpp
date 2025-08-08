#pragma once

#include <array>
#include <chrono>
#include <cstdint>
#include <random>
#include <vector>

class treap {

private:

    static inline std::mt19937 rng = std::mt19937(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );

public:

    using ret_t = std::array<std::int32_t, 2>;

    std::vector<std::int32_t> szs;
    std::vector<std::int32_t> nds_l;
    std::vector<std::int32_t> nds_r;
    std::vector<std::uint32_t> pris;
    std::int32_t idx;

    explicit treap() : treap(0) {}

    explicit treap(std::int32_t sz) : idx(0) {

        szs.reserve(sz);
        nds_l.reserve(sz);
        nds_r.reserve(sz);
        pris.reserve(sz);

    }

    std::int32_t insert() {

        szs.push_back(1);

        nds_l.push_back(-1);
        nds_r.push_back(-1);

        pris.push_back(rng());

        ++idx;

        return idx - 1;

    }

    template <typename F, typename G>
    std::int32_t merge(std::int32_t nd_l, std::int32_t nd_r, F f, G g) {

        if (nd_l == -1) {
            return nd_r;
        }

        if (nd_r == -1) {
            return nd_l;
        }

        g(nd_l);
        g(nd_r);

        if (pris[nd_l] < pris[nd_r]) {
            nds_r[nd_l] = merge(nds_r[nd_l], nd_r, f, g);
            f(nd_l);
            return nd_l;
        } else {
            nds_l[nd_r] = merge(nd_l, nds_l[nd_r], f, g);
            f(nd_r);
            return nd_r;
        }

    }

    template <typename F, typename G, typename H>
    ret_t split(std::int32_t nd, F f, G g, H h) {

        if (nd == -1) {
            return ret_t({-1, -1});
        }

        h(nd);

        if (f(nd)) {
            const auto [splt_l, splt_r] = split(nds_r[nd], f, g, h);
            nds_r[nd] = splt_l;
            g(nd);
            return ret_t({nd, splt_r});
        } else {
            const auto [splt_l, splt_r] = split(nds_l[nd], f, g, h);
            nds_l[nd] = splt_r;
            g(nd);
            return ret_t({splt_l, nd});
        }

    }

};
