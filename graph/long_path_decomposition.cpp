#pragma once

#include <cstdint>
#include <vector>

#include "utility/y_combinator.cpp"

class long_path_decomposition {

private:

    std::vector<std::vector<std::int32_t>> adj;

public:

    std::vector<std::int32_t> dfn;
    std::vector<std::int32_t> chds;
    std::vector<std::int32_t> deps;

    explicit long_path_decomposition(std::int32_t sz) : adj(sz), dfn(sz), chds(sz, -1), deps(sz) {}

    void add_edge(std::int32_t node_1, std::int32_t node_2) {

        adj[node_1].push_back(node_2);
        adj[node_2].push_back(node_1);

    }

    void init(std::int32_t rt) {

        y_combinator(
            [&](auto self, std::int32_t node, std::int32_t par) -> void {
                for (auto x : adj[node]) {
                    if (x != par) {
                        self(x, node);
                        if (deps[x] + 1 > deps[node]) {
                            chds[node] = x;
                            deps[node] = deps[x] + 1;
                        }
                    }
                }
            }
        )(rt, -1);

        std::int32_t nxt = 0;

        y_combinator(
            [&](auto self, std::int32_t node, std::int32_t par) -> void {
                dfn[node] = nxt;
                ++nxt;
                if (chds[node] != -1) {
                    self(chds[node], node);
                }
                for (auto x : adj[node]) {
                    if (x != par && x != chds[node]) {
                        self(x, node);
                    }
                }
            }
        )(rt, -1);

    }

};
