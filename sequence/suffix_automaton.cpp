#pragma once

#include <cstdint>
#include <map>
#include <vector>

template <typename T>
class suffix_automaton {

public:

    std::vector<std::int32_t> lens;
    std::vector<std::map<T, std::int32_t>> adj;
    std::vector<std::int32_t> links;
    std::int32_t idx;
    std::int32_t prv;

    explicit suffix_automaton(
        std::int32_t sz
    ) : lens(sz * 2), adj(sz * 2), links(sz * 2), idx(1), prv(0) {

        links[0] = -1;

    }

    void extend(T val) {

        const std::int32_t cur = idx;
        std::int32_t ptr = prv;

        ++idx;

        lens[cur] = lens[prv] + 1;

        while (ptr != -1 && adj[ptr].count(val) == 0) {
            adj[ptr][val] = cur;
            ptr = links[ptr];
        }

        if (ptr != -1) {
            const std::int32_t nxt = adj[ptr][val];
            if (lens[nxt] != lens[ptr] + 1) {
                const std::int32_t cpy = idx;
                ++idx;
                lens[cpy] = lens[ptr] + 1;
                adj[cpy] = adj[nxt];
                links[cpy] = links[nxt];
                while (ptr != -1 && adj[ptr][val] == nxt) {
                    adj[ptr][val] = cpy;
                    ptr = links[ptr];
                }
                links[nxt] = cpy;
                links[cur] = cpy;
            } else {
                links[cur] = nxt;
            }
        }

        prv = cur;

    }

};
