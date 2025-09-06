#pragma once

#include <array>
#include <cstdint>
#include <queue>
#include <vector>

template <std::int32_t SIGMA>
class aho_corasick_automaton {

public:

    std::vector<std::array<std::int32_t, SIGMA>> adj;
    std::vector<std::int32_t> links;
    std::int32_t ptr;

    explicit aho_corasick_automaton() : adj(1), links(1), ptr(0) {}

    void extend(std::int32_t val) {

        if (adj[ptr][val] == 0) {
            adj[ptr][val] = std::size(adj);
            adj.emplace_back();
            links.emplace_back();
        }

        ptr = adj[ptr][val];

    }

    void init() {

        std::queue<std::int32_t> proc;

        for (auto x : adj[0]) {
            if (x) {
                proc.push(x);
            }
        }

        while (!std::empty(proc)) {
            const std::int32_t node = proc.front();
            proc.pop();
            for (std::int32_t i = 0; i < SIGMA; ++i) {
                std::int32_t& chd = adj[node][i];
                if (chd) {
                    links[chd] = adj[links[node]][i];
                    proc.push(chd);
                } else {
                    chd = adj[links[node]][i];
                }
            }
        }

    }

};
