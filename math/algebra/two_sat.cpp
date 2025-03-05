#pragma once

#include <algorithm>
#include <cstdint>
#include <optional>
#include <vector>

#include "utility/y_combinator.cpp"

class two_sat {

private:

    std::vector<std::vector<std::int32_t>> adj_f;
    std::vector<std::vector<std::int32_t>> adj_r;
    std::int32_t sz;

public:

    explicit two_sat(std::int32_t sz) : adj_f(sz * 2), adj_r(sz * 2), sz(sz) {}

    void add(std::int32_t var_1, std::int32_t neg_1, std::int32_t var_2, std::int32_t neg_2) {

        var_1 = var_1 * 2 ^ neg_1;
        var_2 = var_2 * 2 ^ neg_2;

        adj_f[var_1 ^ 1].push_back(var_2);
        adj_f[var_2 ^ 1].push_back(var_1);
        adj_r[var_2].push_back(var_1 ^ 1);
        adj_r[var_1].push_back(var_2 ^ 1);

    }

    std::optional<std::vector<bool>> solve() const {

        using ret_t = std::optional<std::vector<bool>>;

        std::vector comps(sz * 2, std::int32_t(-1));
        std::int32_t nxt = 0;
        std::vector<std::int32_t> ord;
        std::vector<bool> vals(sz);
        std::vector<bool> vis(sz * 2);

        ord.reserve(sz * 2);

        for (std::int32_t i = 0; i < sz * 2; ++i) {
            if (!vis[i]) {
                y_combinator(
                    [&](auto self, std::int32_t node) -> void {
                        vis[node] = true;
                        for (auto x : adj_f[node]) {
                            if (!vis[x]) {
                                self(x);
                            }
                        }
                        ord.push_back(node);
                    }
                )(i);
            }
        }

        std::reverse(std::begin(ord), std::end(ord));

        for (auto x : ord) {
            if (comps[x] == -1) {
                y_combinator(
                    [&](auto self, std::int32_t node) -> void {
                        comps[node] = nxt;
                        for (auto x : adj_r[node]) {
                            if (comps[x] == -1) {
                                self(x);
                            }
                        }
                    }
                )(x);
                ++nxt;
            }
        }

        for (std::int32_t i = 0; i < sz; ++i) {
            if (comps[i * 2] == comps[i * 2 + 1]) {
                return ret_t();
            }
            vals[i] = comps[i * 2] > comps[i * 2 + 1];
        }

        return ret_t(vals);

    }

};
