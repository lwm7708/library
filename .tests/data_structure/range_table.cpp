#include <array>
#include <cstdint>
#include <queue>
#include <utility>

#include "include/doctest.h"

#include "data_structure/range_table.cpp"

TEST_CASE("range_table") {

    using node_t = std::array<std::int32_t, 2>;

    using init_t = std::pair<node_t, std::int32_t>;

    CHECK(range_table::log_2(11) == 3);
    CHECK(range_table::log_2(32) == 5);

    std::queue<init_t> inits;
    std::queue<node_t> nodes;

    inits.emplace(node_t({0, 0}), 1);
    inits.emplace(node_t({0, 1}), 1);
    inits.emplace(node_t({0, 2}), 1);
    inits.emplace(node_t({0, 3}), 1);

    inits.emplace(node_t({1, 0}), 1);
    inits.emplace(node_t({1, 1}), 1);
    inits.emplace(node_t({1, 2}), 1);
    inits.emplace(node_t({1, 3}), 1);

    inits.emplace(node_t({2, 1}), 1);
    inits.emplace(node_t({2, 0}), 0);
    inits.emplace(node_t({2, 2}), 1);
    inits.emplace(node_t({2, 3}), 0);

    range_table::for_all(
        4,
        [&](std::int32_t lvl, std::int32_t idx, std::int32_t rst) -> void {
            const auto [node, cur_rst] = inits.front();
            if (lvl == node[0] && idx == node[1] && rst == cur_rst) {
                inits.pop();
            }
        }
    );

    CHECK(std::empty(inits));

    nodes.push(node_t({2, 1}));
    nodes.push(node_t({2, 3}));

    const auto pop = [&](std::int32_t lvl, std::int32_t idx) -> void {
        if (lvl == nodes.front()[0] && idx == nodes.front()[1]) {
            nodes.pop();
        }
    };

    range_table::for_rng(1, 4, pop);

    CHECK(std::empty(nodes));

    nodes.push(node_t({0, 1}));

    range_table::for_rng(1, 2, pop);

    CHECK(std::empty(nodes));

}
