#pragma once

#include <cstdint>
#include <functional>
#include <iterator>
#include <limits>
#include <set>

template <typename Compare>
class line_container {

private:

    static constexpr std::int64_t INF = std::numeric_limits<std::int64_t>::max();

    static inline const Compare cmp = Compare();

public:

    class fn {

    public:

        std::int64_t m;
        std::int64_t b;
        mutable std::int64_t crd;

        bool operator<(const fn& other) const {

            return cmp(other.m, m);

        }

        bool operator<(std::int64_t other) const {

            return crd < other;

        }

    };

    std::set<fn, std::less<>> fns;

    void insert(std::int64_t m, std::int64_t b) {

        const fn cur({m, b, 0});

        auto it = fns.upper_bound(cur);

        if (it != std::begin(fns) && m == std::prev(it)->m) {
            const std::int64_t prv_b = std::prev(it)->b;
            if (!cmp(b, prv_b) || b == prv_b) {
                return;
            }
            it = fns.erase(std::prev(it));
        }

        const auto isect = [](const fn& fn_1, const fn& fn_2) -> std::int64_t {
            const std::int64_t den = fn_1.m - fn_2.m;
            const std::int64_t num = fn_2.b - fn_1.b;
            return num / den - ((num ^ den) < 0 && num % den);
        };

        if (it != std::begin(fns) && isect(*std::prev(it), cur) >= std::prev(it)->crd) {
            return;
        }

        it = fns.insert(it, cur);

        while (
            it != std::begin(fns) && std::prev(it) != std::begin(fns) &&
            isect(*std::prev(it), cur) <= isect(*std::prev(it, 2), *std::prev(it))
        ) {
            fns.erase(std::prev(it));
        }

        while (
            it != std::prev(std::end(fns)) && std::next(it) != std::prev(std::end(fns)) &&
            isect(cur, *std::next(it)) >= isect(*std::next(it), *std::next(it, 2))
        ) {
            fns.erase(std::next(it));
        }

        if (it != std::begin(fns)) {
            std::prev(it)->crd = isect(*std::prev(it), cur);
        }

        it->crd = it != std::prev(std::end(fns)) ? isect(cur, *std::next(it)) : INF;

    }

    std::int64_t query(std::int64_t crd) const {

        const auto [m, b, fn_crd] = *fns.lower_bound(crd);

        return m * crd + b;

    }

};
