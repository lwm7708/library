template <typename T, typename U>
auto exponentiate(T base, U pow, const T& id = T(1)) {

    auto res = id;

    while (pow > 0) {
        if (pow & 1) {
            res *= base;
        }
        base *= base;
        pow >>= 1;
    }

    return res;

}
