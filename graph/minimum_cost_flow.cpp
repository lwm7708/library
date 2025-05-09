#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>
#include <queue>
#include <vector>

template <typename T>
class minimum_cost_flow {

private:

    struct edge {

        std::int32_t fm;
        std::int32_t to;
        T cap;
        T cst;

    };

    std::int32_t sz;
    std::vector<edge> edges;
    std::vector<std::vector<std::int32_t>> adj;
    T inf;

public:

    explicit minimum_cost_flow(std::int32_t sz) : sz(sz), adj(sz), inf(1) {}

    void add_edge(std::int32_t node_fm, std::int32_t node_to, T cap, T cst) {

        edges.push_back({node_fm, node_to, cap, cst});
        edges.push_back({node_to, node_fm, 0, -cst});

        adj[node_fm].push_back(std::size(edges) - 2);
        adj[node_to].push_back(std::size(edges) - 1);

        inf += std::abs(cst);

    }

    T get_flow(std::int32_t edge_idx) const {

        return edges[edge_idx * 2 + 1].cap;

    }

    std::array<T, 2> push(std::int32_t src, std::int32_t dst, T mx_flow) {

        T tot_cst = 0;
        T tot_flow = 0;

        while (tot_flow < mx_flow) {
            std::vector csts(sz, inf);
            std::vector<bool> in(sz);
            std::vector pars(sz, std::int32_t(-1));
            std::queue<std::int32_t> proc;
            csts[src] = 0;
            proc.push(src);
            in[src] = true;
            while (!std::empty(proc)) {
                const std::int32_t node = proc.front();
                proc.pop();
                in[node] = false;
                for (auto x : adj[node]) {
                    const auto [fm, to, cap, cst] = edges[x];
                    if (csts[fm] + cst < csts[to] && cap) {
                        csts[to] = csts[fm] + cst;
                        pars[to] = x;
                        if (!in[to]) {
                            proc.push(to);
                            in[to] = true;
                        }
                    }
                }
            }
            if (pars[dst] == -1) {
                break;
            }
            T amt = mx_flow - tot_flow;
            for (std::int32_t i = dst; i != src; i = edges[pars[i]].fm) {
                amt = std::min(amt, edges[pars[i]].cap);
            }
            tot_flow += amt;
            tot_cst += csts[dst] * amt;
            for (std::int32_t i = dst; i != src; i = edges[pars[i]].fm) {
                edges[pars[i]].cap -= amt;
                edges[pars[i] ^ 1].cap += amt;
            }
        }

        return std::array<T, 2>({tot_flow, tot_cst});

    }

};
