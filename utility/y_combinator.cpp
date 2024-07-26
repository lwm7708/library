#include <utility>

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
