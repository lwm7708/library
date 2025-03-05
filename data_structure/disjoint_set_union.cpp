#pragma once

#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

class disjoint_set_union {

private:

    std::vector<std::int32_t> reps;
    std::vector<std::int32_t> szs;

public:

    explicit disjoint_set_union(std::int32_t sz) : reps(sz), szs(sz, 1) {

        std::iota(std::begin(reps), std::end(reps), 0);

    }

    std::int32_t find(std::int32_t node) {

        std::int32_t rep = node;

        while (reps[rep] != rep) {
            rep = reps[rep];
        }

        while (node != rep) {
            node = std::exchange(reps[node], rep);
        }

        return rep;

    }

    std::int32_t get_sz(std::int32_t node) {

        return szs[find(node)];

    }

    void merge(std::int32_t node_1, std::int32_t node_2) {

        node_1 = find(node_1);
        node_2 = find(node_2);

        if (node_1 != node_2) {
            if (szs[node_1] < szs[node_2]) {
                std::swap(node_1, node_2);
            }
            reps[node_2] = node_1;
            szs[node_1] += szs[node_2];
        }

    }

};
