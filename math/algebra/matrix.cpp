#pragma once

#include <cstdint>
#include <utility>
#include <vector>

template <typename T>
class matrix {

private:

    std::int32_t m;
    std::int32_t n;
    std::vector<std::vector<T>> data;

public:

    static matrix get_id(std::int32_t sz) {

        matrix res(sz, sz);

        for (std::int32_t i = 0; i < sz; ++i) {
            res[i][i] = T(1);
        }

        return res;

    }

    explicit matrix(std::int32_t m, std::int32_t n) : m(m), n(n), data(m, std::vector<T>(n)) {}

    std::vector<T>& operator[](std::int32_t row) {

        return data[row];

    }

    const std::vector<T>& operator[](std::int32_t row) const {

        return data[row];

    }

    void operator*=(const matrix& other) {

        matrix res(m, other.n);

        for (std::int32_t i = 0; i < m; ++i) {
            for (std::int32_t j = 0; j < other.n; ++j) {
                for (std::int32_t k = 0; k < n; ++k) {
                    res[i][j] += data[i][k] * other[k][j];
                }
            }
        }

        *this = std::move(res);

    }

    void operator*=(T coef) {

        for (auto& x : data) {
            for (auto& y : x) {
                y *= coef;
            }
        }

    }

    auto begin() {

        return std::begin(data);

    }

    auto begin() const {

        return std::begin(data);

    }

    auto end() {

        return std::end(data);

    }

    auto end() const {

        return std::end(data);

    }

    friend bool operator==(const matrix& lhs, const matrix& rhs) {

        return lhs.data == rhs.data;

    }

    friend bool operator!=(const matrix& lhs, const matrix& rhs) {

        return !(lhs == rhs);

    }

    friend matrix operator*(matrix lhs, const matrix& rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend matrix operator*(matrix lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

};
