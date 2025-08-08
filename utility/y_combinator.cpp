#pragma once

#include <utility>

template <typename F>
class y_combinator {

private:

    F f;

public:

    explicit y_combinator(F&& f) : f(f) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {

        return f(*this, std::forward<Args>(args)...);

    }

};

template <typename F>
y_combinator(F) -> y_combinator<F>;
