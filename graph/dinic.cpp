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
    std::vector<edge_t> edges;
    std::vector<std::vector<std::int32_t>> adj;
    std::vector<std::int32_t> lvls;
    T mx_flow;

public:

    explicit dinic(std::int32_t sz) : sz(sz), adj(sz), lvls(sz), mx_flow(0) {}

    void add_edge(std::int32_t node_fm, std::int32_t node_to, T cap) {

        edges.emplace_back(node_to, cap);
        edges.emplace_back(node_fm, 0);

        adj[node_fm].push_back(std::size(edges) - 2);
        adj[node_to].push_back(std::size(edges) - 1);

        mx_flow += cap;

    }

    bool get_side(std::int32_t node) const {

        return lvls[node] == -1;

    }

    T push(std::int32_t src, std::int32_t sink) {

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
            if (lvls[sink] == -1) {
                break;
            }
            std::vector<std::int32_t> ptrs(sz);
            tot_flow += y_combinator(
                [&](auto self, std::int32_t node, T flow_in) -> T {
                    if (node == sink) {
                        return flow_in;
                    }
                    T flow_ot = 0;
                    while (ptrs[node] < std::int32_t(std::size(adj[node])) && flow_ot < flow_in) {
                        const std::int32_t idx = adj[node][ptrs[node]];
                        auto& [nbr, cap] = edges[idx];
                        if (lvls[nbr] == lvls[node] + 1 && cap) {
                            const T c_flow = self(nbr, std::min(cap, flow_in - flow_ot));
                            flow_ot += c_flow;
                            cap -= c_flow;
                            edges[idx ^ 1].second += c_flow;
                        }
                        ptrs[node] += flow_ot < flow_in;
                    }
                    return flow_ot;
                }
            )(src, mx_flow + 1);
        }

        return tot_flow;

    }

};
