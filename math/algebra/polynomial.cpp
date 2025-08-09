#pragma once

#include <cstdint>
#include <initializer_list>
#include <optional>
#include <vector>

#include "math/algebra/fast_fourier_transform.cpp"
#include "math/combinatorics/exponentiate.cpp"
#include "utility/y_combinator.cpp"

template <typename T, std::int32_t PRT>
class polynomial {

private:

    static inline std::vector<T> rts;

    std::vector<T> coefs;

    polynomial rev(std::int32_t n) const {

        polynomial res(std::rbegin(coefs), std::rbegin(coefs) + std::min(n, size()));

        if (size() < n) {
            res = res.mul_pow(n - size());
        }

        return res;

    }

public:

    static polynomial interp(const std::vector<T>& xs, const std::vector<T>& ys) {

        const std::int32_t sz = std::size(xs);

        const std::int32_t seg_sz = 1 << (31 - __builtin_clz(sz * 2 - 1));

        std::vector seg(seg_sz * 2, polynomial({T(1)}));

        for (std::int32_t i = 0; i < sz; ++i) {
            seg[seg_sz + i] = polynomial({-xs[i], T(1)});
        }

        for (std::int32_t i = seg_sz - 1; i; --i) {
            seg[i] = seg[i << 1] * seg[i << 1 | 1];
        }

        return y_combinator(
            [&](
                auto self, const polynomial& poly, std::int32_t nd, std::int32_t tr_l,
                std::int32_t tr_r
            ) -> polynomial {
                if (tr_l >= sz) {
                    return polynomial();
                }
                if (tr_r - tr_l == 1) {
                    return polynomial({ys[tr_l] / poly[0]});
                }
                const std::int32_t tr_m = (tr_l + tr_r) / 2;
                return self(poly % seg[nd << 1], nd << 1, tr_l, tr_m) * seg[nd << 1 | 1] + self(
                    poly % seg[nd << 1 | 1], nd << 1 | 1, tr_m, tr_r
                ) * seg[nd << 1];
            }
        )(seg[1].deriv(), 1, 0, seg_sz);

    }

    explicit polynomial() = default;

    explicit polynomial(std::int32_t n) : coefs(n) {}

    explicit polynomial(std::initializer_list<T> init) : coefs(init) {}

    template <typename It>
    explicit polynomial(It it_l, It it_r) : coefs(it_l, it_r) {}

    T& operator[](std::int32_t pos) {

        return coefs[pos];

    }

    const T& operator[](std::int32_t pos) const {

        return coefs[pos];

    }

    polynomial operator-() const {

        polynomial res = *this;

        for (auto& x : res.coefs) {
            x = -x;
        }

        return res;

    }

    void operator+=(const polynomial& other) {

        resize(std::max(size(), other.size()));

        for (std::int32_t i = 0; i < other.size(); ++i) {
            coefs[i] += other[i];
        }

        trim();

    }

    void operator-=(const polynomial& other) {

        *this += -other;

    }

    void operator*=(const polynomial& other) {

        static constexpr std::int32_t BND = 8;

        if (is_zero() || other.is_zero()) {
            resize(0);
            return;
        }

        const std::int32_t lg = 31 - __builtin_clz((size() + other.size() - 1) * 2 - 1);
        std::vector vals_1 = coefs;
        std::vector vals_2 = other.coefs;

        if (lg >= BND) {
            const std::int32_t sz = std::size(rts);
            resize(1 << lg);
            vals_1.resize(1 << lg);
            vals_2.resize(1 << lg);
            if (sz <= lg) {
                rts.resize(lg + 1);
                rts[lg] = exponentiate(T(PRT), (T::get_mod() - 1) >> lg);
                for (std::int32_t i = lg - 1; i >= sz; --i) {
                    rts[i] = rts[i + 1] * rts[i + 1];
                }
            }
            vals_1 = fast_fourier_transform(vals_1, 0, rts);
            vals_2 = fast_fourier_transform(vals_2, 0, rts);
            for (std::int32_t i = 0; i < 1 << lg; ++i) {
                coefs[i] = vals_1[i] * vals_2[i];
            }
            coefs = fast_fourier_transform(coefs, 1, rts);
        } else {
            const std::int32_t sz = size();
            coefs.assign(sz + other.size() - 1, T());
            for (std::int32_t i = 0; i < sz; ++i) {
                for (std::int32_t j = 0; j < other.size(); ++j) {
                    coefs[i + j] += vals_1[i] * vals_2[j];
                }
            }
        }

        trim();

    }

    void operator*=(T other) {

        for (auto& x : coefs) {
            x *= other;
        }

        trim();

    }

    void operator/=(const polynomial& other) {

        if (size() < other.size()) {
            resize(0);
            return;
        }

        const std::int32_t n = size() - other.size() + 1;

        *this = (rev(size()).mod_pow(n) * other.rev(other.size()).inv(n)).mod_pow(n).rev(n);

        trim();

    }

    void operator/=(T other) {

        *this *= T(1) / other;

    }

    void operator%=(const polynomial& other) {

        *this -= other * (*this / other);

    }

    T eval(T x) const {

        T res;

        for (std::int32_t i = size() - 1; i >= 0; --i) {
            res = res * x + coefs[i];
        }

        return res;

    }

    std::vector<T> eval(const std::vector<T>& xs) const {

        const std::int32_t sz = std::size(xs);

        if (is_zero()) {
            return std::vector(sz, T());
        }

        std::vector<T> res(sz);
        const std::int32_t seg_sz = 1 << (31 - __builtin_clz(sz * 2 - 1));

        std::vector seg(seg_sz * 2, polynomial({T(1)}));

        for (std::int32_t i = 0; i < sz; ++i) {
            seg[seg_sz + i] = polynomial({-xs[i], T(1)});
        }

        for (std::int32_t i = seg_sz - 1; i; --i) {
            seg[i] = seg[i << 1] * seg[i << 1 | 1];
        }

        y_combinator(
            [&](
                auto self, const polynomial& poly, std::int32_t nd, std::int32_t tr_l,
                std::int32_t tr_r
            ) -> void {
                if (tr_l >= sz) {
                    return;
                }
                if (tr_r - tr_l == 1) {
                    res[tr_l] = poly.eval(xs[tr_l]);
                    return;
                }
                const std::int32_t tr_m = (tr_l + tr_r) / 2;
                self(poly % seg[nd << 1], nd << 1, tr_l, tr_m);
                self(poly % seg[nd << 1 | 1], nd << 1 | 1, tr_m, tr_r);
            }
        )(*this, 1, 0, seg_sz);

        return res;

    }

    void resize(std::int32_t n) {

        coefs.resize(n);

    }

    void trim() {

        while (!is_zero() && coefs.back() == T()) {
            coefs.pop_back();
        }

    }

    std::int32_t trail() const {

        for (std::int32_t i = 0; i < size(); ++i) {
            if (coefs[i] != T()) {
                return i;
            }
        }

        return size();

    }

    bool is_zero() const {

        return size() == 0;

    }

    std::int32_t size() const {

        return std::size(coefs);

    }

    polynomial inv(std::int32_t n) const {

        polynomial res({T(1) / coefs[0]});

        for (std::int32_t i = 1; i < n; i *= 2) {
            res = (res * (polynomial({T(2)}) - mod_pow(i * 2) * res)).mod_pow(i * 2);
        }

        return res.mod_pow(n);

    }

    polynomial exp(std::int32_t n) const {

        polynomial res({T(1)});

        for (std::int32_t i = 1; i < n; i *= 2) {
            res = (res * (mod_pow(i * 2) - res.log(i * 2) + polynomial({T(1)}))).mod_pow(i * 2);
        }

        return res.mod_pow(n);

    }

    polynomial log(std::int32_t n) const {

        return (deriv().mod_pow(n) * inv(n)).integ().mod_pow(n);

    }

    polynomial pow(std::int64_t k, std::int32_t n) const {

        if (k == 0) {
            return polynomial({T(1)});
        }

        if (is_zero()) {
            return polynomial();
        }

        const std::int32_t cnt = trail();

        if (cnt && k >= (n + cnt - 1) / cnt) {
            return polynomial();
        }

        const T coef = coefs[cnt];
        const std::int32_t sz = n - cnt * k;

        return (
            ((div_pow(cnt) / coef).log(sz) * T(k)).exp(sz) * exponentiate(coef, k)
        ).mul_pow(cnt * k);

    }

    std::optional<polynomial> sqrt(std::int32_t n) const {

        if (is_zero()) {
            return std::optional(polynomial());
        }

        const std::int32_t cnt = trail();

        if (cnt % 2) {
            return std::nullopt;
        }

        const T coef = coefs[cnt];
        const std::int32_t sz = n - cnt / 2;

        const std::optional rt = coef.sqrt();

        if (!rt) {
            return std::nullopt;
        }

        return std::optional(
            (((div_pow(cnt) / coef).log(sz) / T(2)).exp(sz) * *rt).mul_pow(cnt / 2)
        );

    }

    polynomial deriv() const {

        if (is_zero()) {
            return polynomial();
        }

        polynomial res(size() - 1);

        for (std::int32_t i = 1; i < size(); ++i) {
            res[i - 1] = coefs[i] * T(i);
        }

        return res;

    }

    polynomial integ() const {

        polynomial res(size() + 1);

        for (std::int32_t i = 0; i < size(); ++i) {
            res[i + 1] = coefs[i] / T(i + 1);
        }

        return res;

    }

    polynomial mul_pow(std::int32_t k) const {

        polynomial res = *this;

        res.coefs.insert(std::begin(res.coefs), k, T());

        res.trim();

        return res;

    }

    polynomial div_pow(std::int32_t k) const {

        if (k >= size()) {
            return polynomial();
        }

        return polynomial(std::begin(coefs) + k, std::end(coefs));

    }

    polynomial mod_pow(std::int32_t k) const {

        if (k >= size()) {
            return *this;
        }

        polynomial res = *this;

        res.resize(k);
        res.trim();

        return res;

    }

    friend bool operator==(const polynomial& lhs, const polynomial& rhs) {

        return lhs.coefs == rhs.coefs;

    }

    friend bool operator!=(const polynomial& lhs, const polynomial& rhs) {

        return !(lhs == rhs);

    }

    friend polynomial operator+(polynomial lhs, const polynomial& rhs) {

        lhs += rhs;

        return lhs;

    }

    friend polynomial operator-(polynomial lhs, const polynomial& rhs) {

        lhs -= rhs;

        return lhs;

    }

    friend polynomial operator*(polynomial lhs, const polynomial& rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend polynomial operator*(polynomial lhs, T rhs) {

        lhs *= rhs;

        return lhs;

    }

    friend polynomial operator/(polynomial lhs, const polynomial& rhs) {

        lhs /= rhs;

        return lhs;

    }

    friend polynomial operator/(polynomial lhs, T rhs) {

        lhs /= rhs;

        return lhs;

    }

    friend polynomial operator%(polynomial lhs, const polynomial& rhs) {

        lhs %= rhs;

        return lhs;

    }

};
