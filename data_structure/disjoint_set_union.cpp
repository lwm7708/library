#include <numeric>
#include <utility>
#include <vector>

class DisjointSetUnion {

private:

    std::vector<int> reps = std::vector<int>();
    std::vector<int> szs = std::vector<int>();

public:

    explicit DisjointSetUnion(int sz) {

        reps.resize(sz);

        std::iota(std::begin(reps), std::end(reps), 0);

        szs.assign(sz, 1);

    }

    auto find(int node) {

        auto ptr = node;

        while (reps[ptr] != ptr) {
            ptr = reps[ptr];
        }

        const auto rep = ptr;

        ptr = node;

        while (ptr != rep) {
            const auto next = reps[ptr];
            reps[ptr] = rep;
            ptr = next;
        }

        return rep;

    }

    auto getSz(int node) {

        return szs[find(node)];

    }

    auto merge(int node_1, int node_2) {

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
