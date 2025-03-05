#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "utility/y_combinator.cpp"

class heavy_light_decomposition {

private:

    std::int32_t sz;
    std::vector<std::vector<std::int32_t>> adj;
    std::vector<std::int32_t> pars;
    std::vector<std::int32_t> deps;
    std::vector<std::int32_t> tops;

public:

    std::vector<std::int32_t> dfn;

    explicit heavy_light_decomposition(
        std::int32_t sz
    ) : sz(sz), adj(sz), pars(sz), deps(sz), tops(sz), dfn(sz) {}

    void add_edge(std::int32_t node_1, std::int32_t node_2) {

        adj[node_1].push_back(node_2);
        adj[node_2].push_back(node_1);

    }

    template <typename F>
    void for_path(std::int32_t node_1, std::int32_t node_2, F f) const {

        while (tops[node_1] != tops[node_2]) {
            if (deps[tops[node_1]] > deps[tops[node_2]]) {
                std::swap(node_1, node_2);
            }
            const std::int32_t top = tops[node_2];
            f(dfn[top], dfn[node_2] + 1);
            node_2 = pars[top];
        }

        if (deps[node_1] > deps[node_2]) {
            std::swap(node_1, node_2);
        }

        f(dfn[node_1], dfn[node_2] + 1);

    }

    void init(std::int32_t rt) {

        std::vector chds(sz, std::int32_t(-1));
        std::int32_t nxt = 0;
        std::vector szs(sz, std::int32_t(1));

        y_combinator(
            [&](auto self, std::int32_t node, std::int32_t par) -> void {
                pars[node] = par;
                deps[node] = par != -1 ? deps[par] + 1 : 0;
                for (auto x : adj[node]) {
                    if (x != par) {
                        self(x, node);
                        if (chds[node] == -1 || szs[x] > szs[chds[node]]) {
                            chds[node] = x;
                        }
                        szs[node] += szs[x];
                    }
                }
            }
        )(rt, -1);

        y_combinator(
            [&](auto self, std::int32_t node) -> void {
                dfn[node] = nxt;
                ++nxt;
                const std::int32_t par = pars[node];
                tops[node] = par != -1 && chds[par] == node ? tops[par] : node;
                if (chds[node] != -1) {
                    self(chds[node]);
                }
                for (auto x : adj[node]) {
                    if (x != par && x != chds[node]) {
                        self(x);
                    }
                }
            }
        )(rt);

    }

};
