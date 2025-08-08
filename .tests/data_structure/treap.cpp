#include <cstdint>

#include "include/doctest.h"

#include "data_structure/treap.cpp"
#include "utility/y_combinator.cpp"

TEST_CASE("treap") {

    std::int32_t nxt = 0;
    std::int32_t rt = -1;
    treap trp(6);

    const auto pull = [&](std::int32_t nd) -> void {
        trp.szs[nd] = 1;
        if (trp.nds_l[nd] != -1) {
            trp.szs[nd] += trp.szs[trp.nds_l[nd]];
        }
        if (trp.nds_r[nd] != -1) {
            trp.szs[nd] += trp.szs[trp.nds_r[nd]];
        }
    };
    const auto push = [](std::int32_t) -> void {};

    const auto merge = [&](std::int32_t nd_l, std::int32_t nd_r) -> std::int32_t {
        return trp.merge(nd_l, nd_r, pull, push);
    };
    const auto split = [&](std::int32_t nd, std::int32_t rnk) -> treap::ret_t {
        return trp.split(
            nd,
            [&](std::int32_t nd) -> bool {
                const std::int32_t sz = trp.nds_l[nd] != -1 ? trp.szs[trp.nds_l[nd]] : 0;
                if (sz < rnk) {
                    rnk -= sz + 1;
                    return true;
                } else {
                    return false;
                }
            }, pull, push
        );
    };

    for (std::int32_t i = 0; i < 6; ++i) {
        rt = merge(rt, trp.insert());
    }

    y_combinator(
        [&](auto self, std::int32_t nd) -> void {
            if (trp.nds_l[nd] != -1) {
                self(trp.nds_l[nd]);
            }
            CHECK(nd == nxt);
            ++nxt;
            if (trp.nds_r[nd] != -1) {
                self(trp.nds_r[nd]);
            }
        }
    )(rt);

    CHECK(trp.idx == 6);
    CHECK(nxt == 6);

    const auto [nd_l, nd_r] = split(rt, 4);

    const auto [splt_l, splt_r] = split(nd_l, 1);

    CHECK(trp.szs[splt_l] == 1);
    CHECK(trp.szs[splt_r] == 3);
    CHECK(trp.szs[nd_r] == 2);

    rt = merge(merge(splt_l, splt_r), nd_r);

    CHECK(trp.szs[rt] == 6);

}
