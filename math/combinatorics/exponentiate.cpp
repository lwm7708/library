#pragma once

template <typename T, typename U>
T exponentiate(T base, U pow, const T& id = T(1)) {

    T res = id;

    while (pow > 0) {
        if (pow & 1) {
            res *= base;
        }
        pow >>= 1;
        base *= base;
    }

    return res;

}
