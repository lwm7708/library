#include <vector>

template <typename T>
class Matrix {

private:

    std::vector<std::vector<T>> data = std::vector<std::vector<T>>();

public:

    static auto getId(int sz) {

        auto res = Matrix(sz, sz);

        for (auto i = 0; i < sz; ++i) {
            res[i][i] = T(1);
        }

        return res;

    }

    int m = 0;
    int n = 0;

    explicit Matrix(int m, int n, T value = T()) : m(m), n(n) {

        data.resize(m, std::vector<T>(n, value));

    }

    auto& operator[](int row) {

        return data[row];

    }

    const auto& operator[](int row) const {

        return data[row];

    }

    auto operator+=(const Matrix& other) {

        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                data[i][j] += other[i][j];
            }
        }

    }

    auto operator-=(const Matrix& other) {

        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                data[i][j] -= other[i][j];
            }
        }

    }

    auto operator*=(const Matrix& other) {

        auto res = Matrix(m, other.n);

        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < other.n; ++j) {
                for (auto k = 0; k < n; ++k) {
                    res[i][j] += data[i][k] * other[k][j];
                }
            }
        }

        *this = res;

    }

    auto operator*=(T coef) {

        for (auto& x : data) {
            for (auto& y : x) {
                y *= coef;
            }
        }

    }

    auto operator/=(T div) {

        for (auto& x : data) {
            for (auto& y : x) {
                y /= div;
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

    friend auto operator+(Matrix lhs, const Matrix& rhs) {

        lhs += rhs;

        return lhs;

    }

    friend auto operator-(Matrix lhs, const Matrix& rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend auto operator*(Matrix lhs, const Matrix& rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator*(Matrix lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend auto operator/(Matrix lhs, T rhs) {

        lhs /= rhs;

        return lhs;

    }

    friend auto operator*(T lhs, const Matrix& rhs) {

        return rhs * lhs;

    }

};
