#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

template <typename F>
class YCombinator {

private:

    const F f = nullptr;

public:

    explicit YCombinator(F&& f) : f(f) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {

        return f(*this, std::forward<Args>(args)...);

    }

};

template <typename F>
YCombinator(F) -> YCombinator<F>;

template <typename T>
class Dinic {

private:

    using Edge = std::pair<int, T>;

    T mx_flow = 0;
    int sz = 0;

public:

    std::vector<std::vector<int>> adj = std::vector<std::vector<int>>();
    std::vector<Edge> edges = std::vector<Edge>();
    std::vector<int> lvls = std::vector<int>();

    explicit Dinic(int sz) : sz(sz) {

        adj.resize(sz);

        lvls.resize(sz);

    }

    auto addEdge(int node_f, int node_t, T cap) {

        edges.emplace_back(node_t, cap);
        edges.emplace_back(node_f, 0);

        adj[node_f].push_back(std::size(edges) - 2);
        adj[node_t].push_back(std::size(edges) - 1);

        mx_flow += cap;

    }

    auto pushFlow(int src, int sink) {

        auto tot_flow = T();

        while (true) {
            std::fill_n(std::begin(lvls), sz, -1);
            lvls[src] = 0;
            auto proc = std::queue<int>();
            proc.push(src);
            while (!std::empty(proc)) {
                const auto node = proc.front();
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
            auto ptrs = std::vector<int>(sz);
            tot_flow += YCombinator(
                [&](auto self, int node, T flow_i) {
                    if (node == sink) {
                        return flow_i;
                    }
                    auto flow_o = T();
                    while (ptrs[node] < static_cast<int>(std::size(adj[node])) && flow_o < flow_i) {
                        const auto edge_idx = adj[node][ptrs[node]];
                        auto& [nbr, cap] = edges[edge_idx];
                        if (lvls[nbr] == lvls[node] + 1 && cap) {
                            const auto c_flow = self(nbr, std::min(cap, flow_i - flow_o));
                            flow_o += c_flow;
                            cap -= c_flow;
                            edges[edge_idx ^ 1].second += c_flow;
                        }
                        ptrs[node] += flow_o < flow_i;
                    }
                    return flow_o;
                }
            )(src, mx_flow + 1);
        }

        return tot_flow;

    }

};
