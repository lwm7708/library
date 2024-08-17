#pragma once

template <typename T, typename U>
T exponentiate(T base, U pwr, const T& id = T(1)) {

    T res = id;

    while (pwr > 0) {
        if (pwr & 1) {
            res *= base;
        }
        pwr >>= 1;
        base *= base;
    }

    return res;

}
