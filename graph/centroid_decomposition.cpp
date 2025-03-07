#pragma once

#include <cstdint>
#include <set>
#include <vector>

#include "utility/y_combinator.cpp"

std::vector<std::int32_t> centroid_decomposition(
    const std::vector<std::int32_t>& nodes_1, const std::vector<std::int32_t>& nodes_2
) {

    const std::int32_t sz = std::size(nodes_1) + 1;

    std::vector<std::set<std::int32_t>> adj(sz);
    std::vector<std::int32_t> pars(sz);
    std::vector<std::int32_t> szs(sz);

    for (std::int32_t i = 0; i < sz - 1; ++i) {
        adj[nodes_1[i]].insert(nodes_2[i]);
        adj[nodes_2[i]].insert(nodes_1[i]);
    }

    y_combinator(
        [&](auto self, std::int32_t rt, std::int32_t par) -> void {
            y_combinator(
                [&](auto self, std::int32_t node, std::int32_t par) -> void {
                    szs[node] = 1;
                    for (auto x : adj[node]) {
                        if (x != par) {
                            self(x, node);
                            szs[node] += szs[x];
                        }
                    }
                }
            )(rt, -1);
            const std::int32_t cntrd = y_combinator(
                [&](auto self, std::int32_t node, std::int32_t par) -> std::int32_t {
                    for (auto x : adj[node]) {
                        if (x != par && szs[x] > szs[rt] / 2) {
                            return self(x, node);
                        }
                    }
                    return node;
                }
            )(rt, -1);
            pars[cntrd] = par;
            for (auto x : adj[cntrd]) {
                adj[x].erase(cntrd);
                self(x, cntrd);
            }
            adj[cntrd].clear();
        }
    )(0, -1);

    return pars;

}
