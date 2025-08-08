#pragma once

#include <algorithm>
#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

#include "utility/y_combinator.cpp"

template <typename T>
class dinic {

private:

    using edge_t = std::pair<std::int32_t, T>;

    std::int32_t sz;
    std::vector<std::vector<std::int32_t>> adj;
    T inf;

public:

    std::vector<edge_t> edges;

    explicit dinic(std::int32_t sz) : sz(sz), adj(sz), inf(1) {}

    void add_edge(std::int32_t node_1, std::int32_t node_2, T cap) {

        edges.emplace_back(node_2, cap);
        edges.emplace_back(node_1, 0);

        adj[node_1].push_back(std::size(edges) - 2);
        adj[node_2].push_back(std::size(edges) - 1);

        inf += cap;

    }

    T push(std::int32_t src, std::int32_t dst) {

        std::vector<std::int32_t> lvls(sz);
        T tot_flow = 0;

        while (true) {
            std::fill_n(std::begin(lvls), sz, -1);
            lvls[src] = 0;
            std::queue<std::int32_t> proc;
            proc.push(src);
            while (!std::empty(proc)) {
                const std::int32_t node = proc.front();
                proc.pop();
                for (auto x : adj[node]) {
                    const auto& [nbr, cap] = edges[x];
                    if (lvls[nbr] == -1 && cap) {
                        lvls[nbr] = lvls[node] + 1;
                        proc.push(nbr);
                    }
                }
            }
            if (lvls[dst] == -1) {
                break;
            }
            std::vector<std::int32_t> ptrs(sz);
            tot_flow += y_combinator(
                [&](auto self, std::int32_t node, T amt) -> T {
                    if (node == dst) {
                        return amt;
                    }
                    T flow = 0;
                    while (ptrs[node] < std::int32_t(std::size(adj[node])) && flow < amt) {
                        const std::int32_t idx = adj[node][ptrs[node]];
                        auto& [nbr, cap] = edges[idx];
                        if (lvls[nbr] == lvls[node] + 1 && cap) {
                            const T cur = self(nbr, std::min(cap, amt - flow));
                            flow += cur;
                            cap -= cur;
                            edges[idx ^ 1].second += cur;
                        }
                        ptrs[node] += flow < amt;
                    }
                    return flow;
                }
            )(src, inf);
        }

        return tot_flow;

    }

};
