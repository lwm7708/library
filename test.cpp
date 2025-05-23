#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "include/doctest.h"

#include "data_structure/bitset.cpp"
#include "data_structure/disjoint_set_union.cpp"
#include "data_structure/fenwick_tree.cpp"
#include "data_structure/line_container.cpp"
#include "data_structure/range_table.cpp"
#include "data_structure/segment_tree.cpp"
#include "data_structure/treap.cpp"
#include "graph/centroid_decomposition.cpp"
#include "graph/dinic.cpp"
#include "graph/heavy_light_decomposition.cpp"
#include "graph/long_path_decomposition.cpp"
#include "graph/minimum_cost_flow.cpp"
#include "hashing/integral_hash.cpp"
#include "math/algebra/diophantine.cpp"
#include "math/algebra/fast_fourier_transform.cpp"
#include "math/algebra/matrix.cpp"
#include "math/algebra/two_sat.cpp"
#include "math/algebra/xor_basis.cpp"
#include "math/combinatorics/combinatorics.cpp"
#include "math/combinatorics/exponentiate.cpp"
#include "math/geometry/point.cpp"
#include "math/geometry/polygon.cpp"
#include "math/geometry/segment.cpp"
#include "math/number_theory/dynamic_modular_integer.cpp"
#include "math/number_theory/extended_gcd.cpp"
#include "math/number_theory/miller_rabin.cpp"
#include "math/number_theory/modular_congruence.cpp"
#include "math/number_theory/modular_integer.cpp"
#include "math/number_theory/pollard_rho.cpp"
#include "math/number_theory/sieve.cpp"
#include "sequence/kasai.cpp"
#include "sequence/manacher.cpp"
#include "sequence/prefix_function.cpp"
#include "sequence/sequence_hasher.cpp"
#include "sequence/suffix_array.cpp"
#include "sequence/suffix_automaton.cpp"
#include "sequence/z_function.cpp"
#include "utility/y_combinator.cpp"

TEST_CASE("bitset") {

    bitset st_1(4);
    bitset st_2(4);
    bitset st_3;

    st_1[1] = true;
    st_1[2] = true;
    st_2[2] = true;
    st_2[3] = true;

    CHECK(!st_1[0]);
    CHECK(st_1[2]);
    CHECK((~st_1)[0]);
    CHECK(!(~st_1)[2]);

    st_1 &= st_2;

    CHECK(!st_1[0]);
    CHECK(!st_1[1]);
    CHECK(st_1[2]);
    CHECK(!st_1[3]);

    st_1[1] = true;
    st_1[2] = true;

    st_1 |= st_2;

    CHECK(!st_1[0]);
    CHECK(st_1[1]);
    CHECK(st_1[2]);
    CHECK(st_1[3]);

    st_1[3] = false;

    st_1 ^= st_2;

    CHECK(!st_1[0]);
    CHECK(st_1[1]);
    CHECK(!st_1[2]);
    CHECK(st_1[3]);

    st_1 >>= 2;

    CHECK(!st_1[0]);
    CHECK(st_1[1]);
    CHECK(!st_1[2]);
    CHECK(!st_1[3]);

    st_1 <<= 1;

    CHECK(!st_1[0]);
    CHECK(!st_1[1]);
    CHECK(st_1[2]);
    CHECK(!st_1[3]);

    st_1 >>= 5;

    for (std::int32_t i = 0; i < 4; ++i) {
        CHECK(!st_1[i]);
    }

    CHECK(!st_1.all());
    CHECK(!st_1.any());
    CHECK(st_1.none());

    CHECK(!st_2.all());
    CHECK(st_2.any());
    CHECK(!st_2.none());

    st_2[0] = true;
    st_2[1] = true;

    CHECK(st_2.all());
    CHECK(st_2.any());
    CHECK(!st_2.none());

    st_1.set();
    st_2.reset();

    CHECK(st_1.all());
    CHECK(st_1.any());
    CHECK(!st_1.none());

    CHECK(!st_2.all());
    CHECK(!st_2.any());
    CHECK(st_2.none());

    CHECK(st_1.count() == 4);
    CHECK(st_2.count() == 0);

    st_1[2] = false;
    st_1[3] = false;

    st_1.flip();

    CHECK(!st_1[0]);
    CHECK(!st_1[1]);
    CHECK(st_1[2]);
    CHECK(st_1[3]);

    CHECK(st_1.count() == 2);

    CHECK(!(st_1 == st_2));
    CHECK(st_1 != st_2);

    st_2[2] = true;
    st_2[3] = true;

    CHECK(st_1 == st_2);
    CHECK(!(st_1 != st_2));

    st_1.reset();
    st_2.reset();

    st_1[1] = true;
    st_1[2] = true;
    st_2[2] = true;
    st_2[3] = true;

    st_3 = st_1 & st_2;

    CHECK(!st_3[0]);
    CHECK(!st_3[1]);
    CHECK(st_3[2]);
    CHECK(!st_3[3]);

    st_3 = st_1 | st_2;

    CHECK(!st_3[0]);
    CHECK(st_3[1]);
    CHECK(st_3[2]);
    CHECK(st_3[3]);

    st_3 = st_1 ^ st_2;

    CHECK(!st_3[0]);
    CHECK(st_3[1]);
    CHECK(!st_3[2]);
    CHECK(st_3[3]);

    st_3 = st_1 >> 2;

    CHECK(st_3[0]);
    CHECK(!st_3[1]);
    CHECK(!st_3[2]);
    CHECK(!st_3[3]);

    st_3 = (st_1 >> 2) << 1;

    CHECK(!st_3[0]);
    CHECK(st_3[1]);
    CHECK(!st_3[2]);
    CHECK(!st_3[3]);

    st_3 = ((st_1 >> 2) << 1) >> 5;

    CHECK(!st_3[0]);
    CHECK(!st_3[1]);
    CHECK(!st_3[2]);
    CHECK(!st_3[3]);

}

TEST_CASE("centroid_decomposition") {

    using vec_t = std::vector<std::int32_t>;

    CHECK(centroid_decomposition(vec_t({0, 1}), vec_t({1, 2})) == vec_t({1, -1, 1}));
    CHECK(
        centroid_decomposition(vec_t({0, 0, 1, 3, 3}), vec_t({1, 3, 2, 4, 5})) == vec_t(
            {-1, 0, 1, 0, 3, 3}
        )
    );

}

TEST_CASE("combinatorics") {

    combinatorics<modular_integer<53>> comb;

    CHECK(comb.comb(2, 3).val == 0);
    CHECK(comb.comb(2, -1).val == 0);
    CHECK(comb.comb(8, 3).val == 3);
    CHECK(comb.comb(51, 8).val == 9);

    CHECK(comb.fact(-3).val == 0);
    CHECK(comb.fact(8).val == 40);
    CHECK(comb.fact(51).val == 1);

    CHECK(comb.inv(-3).val == 0);
    CHECK(comb.inv(8).val == 20);
    CHECK(comb.inv(51).val == 26);

    CHECK(comb.inv_fact(-3).val == 0);
    CHECK(comb.inv_fact(8).val == 4);
    CHECK(comb.inv_fact(51).val == 1);

}

TEST_CASE("dinic") {

    dinic<std::int32_t> ntwk(6);

    ntwk.add_edge(0, 1, 7);
    ntwk.add_edge(0, 2, 4);
    ntwk.add_edge(2, 1, 3);
    ntwk.add_edge(1, 4, 3);
    ntwk.add_edge(1, 3, 5);
    ntwk.add_edge(2, 4, 2);
    ntwk.add_edge(4, 3, 3);
    ntwk.add_edge(4, 5, 5);
    ntwk.add_edge(3, 5, 8);

    CHECK(ntwk.push(0, 5) == 10);

    CHECK(ntwk.get_flow(3) == 3);
    CHECK(ntwk.get_flow(4) == 5);
    CHECK(ntwk.get_flow(5) == 2);
    CHECK(ntwk.get_flow(7) == 5);
    CHECK(ntwk.get_flow(8) == 5);

}

TEST_CASE("diophantine") {

    std::optional<std::array<std::int32_t, 2>> res = diophantine<std::int32_t>(0, 0, 0);

    CHECK(res);

    CHECK((*res)[0] * 0 + (*res)[1] * 0 == 0);

    res = diophantine<std::int32_t>(0, 0, 1);

    CHECK(!res);

    res = diophantine<std::int32_t>(3, 5, -1);

    CHECK(res);

    CHECK((*res)[0] * 3 + (*res)[1] * 5 == -1);

    res = diophantine<std::int32_t>(2, 4, -3);

    CHECK(!res);

    res = diophantine<std::int32_t>(3, 0, -9);

    CHECK(res);

    CHECK((*res)[0] * 3 + (*res)[1] * 0 == -9);

}

TEST_CASE("disjoint_set_union") {

    disjoint_set_union comps(4);

    for (std::int32_t i = 0; i < 4; ++i) {
        CHECK(comps.find(i) == i);
    }

    comps.merge(0, 2);

    CHECK(comps.find(0) == comps.find(2));
    CHECK(comps.find(0) != comps.find(1));

    CHECK(comps.get_sz(0) == 2);

    comps.merge(2, 3);

    CHECK(comps.get_sz(1) == 1);
    CHECK(comps.get_sz(3) == 3);

}

TEST_CASE("dynamic_modular_integer") {

    using num_t = dynamic_modular_integer<0>;

    num_t::set_modulus(7);

    CHECK(num_t::get_modulus() == 7);

    num_t::set_modulus(53);

    CHECK(num_t::get_modulus() == 53);

    CHECK(num_t(2).val == num_t(108).val);
    CHECK(num_t(-2).val == num_t(51).val);
    CHECK((-num_t(2)).val == num_t(51).val);

    num_t num_1(51);
    num_t num_2;

    ++num_1;
    --num_2;

    CHECK(num_1.val == 52);
    CHECK(num_2.val == 52);

    ++num_1;

    CHECK(num_1.val == 0);

    num_1 += num_2 * num_t(2);

    CHECK(num_1.val == 51);

    num_1 -= num_t(-1);

    CHECK(num_1.val == 52);

    num_1 *= num_t(3);

    CHECK(num_1.val == 50);

    num_1 /= num_t(3);

    CHECK(num_1.val == 52);

    CHECK((num_t(-2) + num_t(-3)).val == 48);
    CHECK((num_t(-2) - num_t(-3)).val == 1);
    CHECK((num_t(-2) * num_t(3)).val == 47);
    CHECK((num_t(-2) / num_t(3)).val == 17);

}

TEST_CASE("exponentiate") {

    using mat_t = matrix<std::int32_t>;

    CHECK(exponentiate(std::int32_t(3), 9) == 19683);

    CHECK(exponentiate(modular_integer<53>(7), 123).val == 11);

    mat_t mat(2, 2);

    mat[0][0] = 3;
    mat[0][1] = 8;
    mat[1][0] = 2;
    mat[1][1] = -1;

    mat = exponentiate(mat, 5, mat_t::get_id(2));

    CHECK(mat[0][0] == 3411);
    CHECK(mat[0][1] == 4840);
    CHECK(mat[1][0] == 1210);
    CHECK(mat[1][1] == 991);

}

TEST_CASE("extended_gcd") {

    std::array<std::int32_t, 3> res = extended_gcd<std::int32_t>(12, 27);

    CHECK(res[0] == std::gcd(12, 27));

    CHECK(res[1] * 12 + res[2] * 27 == res[0]);

    res = extended_gcd(37, 4);

    CHECK(res[0] == std::gcd(37, 4));

    CHECK(res[1] * 37 + res[2] * 4 == res[0]);

}

TEST_CASE("fast_fourier_transform") {

    using num_t = modular_integer<998244353>;

    std::vector poly({num_t(3), num_t(7), num_t(4), num_t(2)});
    const std::vector rts({num_t(1), num_t(998244352), num_t(911660635)});

    poly = fast_fourier_transform(poly, 0, rts);

    CHECK(poly[0].val == 16);
    CHECK(poly[1].val == 565325762);
    CHECK(poly[2].val == 998244351);
    CHECK(poly[3].val == 432918589);

    poly = fast_fourier_transform(poly, 1, rts);

    CHECK(poly[0].val == 3);
    CHECK(poly[1].val == 7);
    CHECK(poly[2].val == 4);
    CHECK(poly[3].val == 2);

}

TEST_CASE("fenwick_tree") {

    std::queue<std::int32_t> nds;

    nds.push(3);
    nds.push(4);
    nds.push(8);

    const auto pop = [&](std::int32_t nd) -> void {
        if (nd == nds.front()) {
            nds.pop();
        }
    };

    fenwick_tree::for_pars(2, 8, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(4);

    fenwick_tree::for_rng(6, pop);

    CHECK(std::empty(nds));

}

TEST_CASE("heavy_light_decomposition") {

    using rng_t = std::array<std::int32_t, 2>;
    using vec_t = std::vector<std::int32_t>;

    heavy_light_decomposition decomp(11);

    decomp.add_edge(0, 1);
    decomp.add_edge(0, 2);
    decomp.add_edge(1, 3);
    decomp.add_edge(1, 4);
    decomp.add_edge(3, 5);
    decomp.add_edge(4, 6);
    decomp.add_edge(4, 7);
    decomp.add_edge(2, 8);
    decomp.add_edge(8, 9);
    decomp.add_edge(5, 10);

    decomp.init(0);

    CHECK(decomp.dfn == vec_t({0, 1, 8, 2, 5, 3, 6, 7, 9, 10, 4}));

    std::queue<rng_t> rngs;

    rngs.push(rng_t({7, 8}));
    rngs.push(rng_t({5, 6}));
    rngs.push(rng_t({1, 4}));

    const auto pop = [&](std::int32_t idx_l, std::int32_t idx_r) -> void {
        if (rngs.front() == rng_t({idx_l, idx_r})) {
            rngs.pop();
        }
    };

    decomp.for_path(5, 7, pop);

    CHECK(std::empty(rngs));

    rngs.push(rng_t({8, 11}));
    rngs.push(rng_t({0, 1}));

    decomp.for_path(9, 0, pop);

    decomp = heavy_light_decomposition(4);

    decomp.add_edge(2, 3);
    decomp.add_edge(3, 1);
    decomp.add_edge(0, 1);

    decomp.init(1);

    CHECK(decomp.dfn == vec_t({3, 0, 2, 1}));

    rngs.push(rng_t({1, 2}));

    decomp.for_path(3, 3, pop);

    CHECK(std::empty(rngs));

}

TEST_CASE("integral_hash") {

    const integral_hash hshr;

    CHECK(hshr(33) != hshr(89));
    CHECK(hshr(33) != hshr(-23));
    CHECK(hshr(33) == hshr(33));

}

TEST_CASE("kasai") {

    using vec_t = std::vector<std::int32_t>;

    const std::string str("dcafac ");

    CHECK(kasai(std::begin(str), vec_t({6, 4, 2, 5, 1, 0, 3})) == vec_t({0, 1, 0, 1, 0, 0}));

}

TEST_CASE("line_container") {

    line_container<std::less<>> cont_1;
    line_container<std::greater<>> cont_2;

    cont_1.insert(2, 3);
    cont_2.insert(2, 3);

    CHECK(cont_1.query(3) == 9);
    CHECK(cont_2.query(3) == 9);

    cont_1.insert(-4, 10);
    cont_2.insert(-4, 10);

    CHECK(cont_1.query(-3) == -3);
    CHECK(cont_2.query(-3) == 22);

    cont_1.insert(0, 22);
    cont_2.insert(0, 22);

    CHECK(cont_1.query(0) == 3);
    CHECK(cont_2.query(0) == 22);

    cont_1.insert(0, 26);
    cont_2.insert(0, 26);

    CHECK(cont_1.query(0) == 3);
    CHECK(cont_2.query(0) == 26);

    cont_1.insert(-1, 4);
    cont_2.insert(-1, 4);

    CHECK(cont_1.query(-9) == -15);
    CHECK(cont_1.query(20) == -70);
    CHECK(cont_2.query(-9) == 46);
    CHECK(cont_2.query(20) == 43);

}

TEST_CASE("long_path_decomposition") {

    using vec_t = std::vector<std::int32_t>;

    long_path_decomposition decomp(11);

    decomp.add_edge(0, 1);
    decomp.add_edge(0, 2);
    decomp.add_edge(1, 3);
    decomp.add_edge(1, 4);
    decomp.add_edge(3, 5);
    decomp.add_edge(4, 6);
    decomp.add_edge(4, 7);
    decomp.add_edge(2, 8);
    decomp.add_edge(8, 9);
    decomp.add_edge(5, 10);

    decomp.init(0);

    CHECK(decomp.dfn == vec_t({0, 1, 8, 2, 5, 3, 6, 7, 9, 10, 4}));
    CHECK(decomp.chds == vec_t({1, 3, 8, 5, 6, 10, -1, -1, 9, -1, -1}));
    CHECK(decomp.deps == vec_t({4, 3, 2, 2, 1, 1, 0, 0, 1, 0, 0}));

    decomp = long_path_decomposition(4);

    decomp.add_edge(2, 3);
    decomp.add_edge(3, 1);
    decomp.add_edge(0, 1);

    decomp.init(1);

    CHECK(decomp.dfn == vec_t({3, 0, 2, 1}));
    CHECK(decomp.chds == vec_t({-1, 3, -1, 2}));
    CHECK(decomp.deps == vec_t({0, 2, 0, 1}));

}

TEST_CASE("manacher") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abcba");

    CHECK(manacher(std::begin(str), std::end(str)) == vec_t({1, 1, 3, 1, 1}));

    str.assign("abbbcbbcaaac");

    CHECK(manacher(std::begin(str), std::end(str)) == vec_t({1, 1, 2, 1, 3, 1, 1, 1, 1, 3, 1, 1}));

}

TEST_CASE("matrix") {

    using mat_t = matrix<std::int32_t>;
    using vec_t = std::vector<std::int32_t>;

    mat_t mat_1(2, 2);
    mat_t mat_2(2, 3);

    mat_1[0][1] = 3;
    mat_1[1][0] = 1;
    mat_1[1][1] = 2;

    mat_2[0] = vec_t({-3, 2, 5});
    mat_2[1] = vec_t({3, 8, -9});

    CHECK(mat_1[0] == vec_t({0, 3}));
    CHECK(mat_1[1] == vec_t({1, 2}));

    vec_t& vec = mat_1[1];

    vec[0] = 2;

    CHECK(mat_1[0] == vec_t({0, 3}));
    CHECK(mat_1[1] == vec_t({2, 2}));

    mat_t mat_3 = mat_1;

    mat_1 += mat_1;

    CHECK(mat_1[0] == vec_t({0, 6}));
    CHECK(mat_1[1] == vec_t({4, 4}));

    mat_1 *= 3;

    CHECK(mat_1[0] == vec_t({0, 18}));
    CHECK(mat_1[1] == vec_t({12, 12}));

    mat_1 -= mat_3 * 3;
    mat_1 -= 2 * mat_3;

    CHECK(mat_1[0] == vec_t({0, 3}));
    CHECK(mat_1[1] == vec_t({2, 2}));

    CHECK(mat_1 * mat_t::get_id(2) == mat_1);

    mat_1 *= mat_2;

    mat_3 = mat_t(2, 3);

    mat_3[0] = vec_t({9, 24, -27});
    mat_3[1] = vec_t({0, 20, -8});

    CHECK(mat_1 == mat_3);
    CHECK(mat_1 != mat_3 * 2);

    mat_1 = mat_t(2, 2);

    mat_1[0] = vec_t({0, 3});
    mat_1[1] = vec_t({2, 2});

    CHECK(mat_1 * mat_2 == mat_3);

    mat_2 = mat_t(2, 2);

    mat_2[0] = vec_t({-3, -5});
    mat_2[1] = vec_t({9, 7});

    mat_3 = mat_1 + mat_2;

    CHECK(mat_3[0] == vec_t({-3, -2}));
    CHECK(mat_3[1] == vec_t({11, 9}));

    mat_3 = mat_1 - mat_2;

    CHECK(mat_3[0] == vec_t({3, 8}));
    CHECK(mat_3[1] == vec_t({-7, -5}));

}

TEST_CASE("miller_rabin") {

    CHECK(!miller_rabin(1));
    CHECK(miller_rabin(2));
    CHECK(miller_rabin(7));
    CHECK(!miller_rabin(51));
    CHECK(!miller_rabin(129));
    CHECK(!miller_rabin(2048));
    CHECK(miller_rabin(7901));
    CHECK(miller_rabin(37139213));
    CHECK(miller_rabin(174440041));
    CHECK(!miller_rabin(1437155053));
    CHECK(!miller_rabin(57882617207));
    CHECK(miller_rabin(180252380737439));

}

TEST_CASE("minimum_cost_flow") {

    minimum_cost_flow<std::int32_t> ntwk(5);

    ntwk.add_edge(0, 1, 3, 1);
    ntwk.add_edge(1, 4, 4, 1);
    ntwk.add_edge(2, 0, 3, 9);
    ntwk.add_edge(2, 3, 2, -2);
    ntwk.add_edge(3, 1, 8, 0);

    CHECK(ntwk.push(2, 4, 1) == std::array<std::int32_t, 2>({1, -1}));

    CHECK(ntwk.get_flow(0) == 0);
    CHECK(ntwk.get_flow(1) == 1);
    CHECK(ntwk.get_flow(2) == 0);
    CHECK(ntwk.get_flow(3) == 1);
    CHECK(ntwk.get_flow(4) == 1);

    ntwk = minimum_cost_flow<std::int32_t>(5);

    ntwk.add_edge(0, 1, 3, 1);
    ntwk.add_edge(1, 4, 4, 1);
    ntwk.add_edge(2, 0, 3, 9);
    ntwk.add_edge(2, 3, 2, -2);
    ntwk.add_edge(3, 1, 8, 0);

    CHECK(ntwk.push(2, 4, 5) == std::array<std::int32_t, 2>({4, 20}));

    CHECK(ntwk.get_flow(0) == 2);
    CHECK(ntwk.get_flow(1) == 4);
    CHECK(ntwk.get_flow(2) == 2);
    CHECK(ntwk.get_flow(3) == 2);
    CHECK(ntwk.get_flow(4) == 2);

}

TEST_CASE("modular_congruence") {

    modular_congruence cong(3, 1);

    cong &= modular_congruence(2, 0);

    CHECK(cong.m == 6);
    CHECK(cong.a == 4);

    cong &= modular_congruence(5, 1);

    CHECK(cong.m == 30);
    CHECK(cong.a == 16);

    cong &= modular_congruence(4, 3);

    CHECK(cong.m == 0);

    cong = modular_congruence(6, 3) & modular_congruence(8, 5);

    CHECK(cong.m == 24);
    CHECK(cong.a == 21);

}

TEST_CASE("modular_integer") {

    using num_t = modular_integer<53>;

    CHECK(num_t(2).val == num_t(108).val);
    CHECK(num_t(-2).val == num_t(51).val);
    CHECK((-num_t(2)).val == num_t(51).val);

    num_t num_1(51);
    num_t num_2;

    ++num_1;
    --num_2;

    CHECK(num_1.val == 52);
    CHECK(num_2.val == 52);

    ++num_1;

    CHECK(num_1.val == 0);

    num_1 += num_2 * num_t(2);

    CHECK(num_1.val == 51);

    num_1 -= num_t(-1);

    CHECK(num_1.val == 52);

    num_1 *= num_t(3);

    CHECK(num_1.val == 50);

    num_1 /= num_t(3);

    CHECK(num_1.val == 52);

    CHECK((num_t(-2) + num_t(-3)).val == 48);
    CHECK((num_t(-2) - num_t(-3)).val == 1);
    CHECK((num_t(-2) * num_t(3)).val == 47);
    CHECK((num_t(-2) / num_t(3)).val == 17);

}

TEST_CASE("point") {

    using pt_t = point<std::int32_t>;

    constexpr double EPS = 1e-8;

    pt_t pt_1(2, -4);
    pt_t pt_2(7, 8);

    CHECK(pt_t::cross(pt_1, pt_2) == 44);

    CHECK(pt_t::dot(pt_1, pt_2) == -18);

    CHECK(pt_1 != pt_2);

    CHECK(-pt_1 == pt_t(-2, 4));

    pt_1 += pt_2;

    CHECK(pt_1 == pt_t(9, 4));

    pt_1 -= pt_2;

    CHECK(pt_1 == pt_t(2, -4));

    pt_1 *= 3;

    CHECK(pt_1 == pt_t(6, -12));

    pt_1 /= 2;

    CHECK(pt_1 == pt_t(3, -6));

    CHECK(std::abs(pt_1.length() - std::sqrt(45)) < EPS);

    CHECK(pt_1.norm() == 45);

    pt_1 = pt_t(22, -4);
    pt_2 = pt_t(3, 4);

    CHECK(pt_1 + pt_2 == pt_t(25, 0));

    CHECK(pt_1 - pt_2 == pt_t(19, -8));

    CHECK(pt_1 * 2 == pt_t(44, -8));
    CHECK(2 * pt_1 == pt_t(44, -8));

    CHECK(pt_1 / 2 == pt_t(11, -2));

}

TEST_CASE("pollard_rho") {

    std::int64_t dvsr = pollard_rho(51);

    CHECK(dvsr != 51);

    CHECK(51 % dvsr == 0);

    dvsr = pollard_rho(129);

    CHECK(dvsr != 129);

    CHECK(129 % dvsr == 0);

    dvsr = pollard_rho(2048);

    CHECK(dvsr != 2048);

    CHECK(2048 % dvsr == 0);

    dvsr = pollard_rho(1437155053);

    CHECK(dvsr != 1437155053);

    CHECK(1437155053 % dvsr == 0);

    dvsr = pollard_rho(57882617207);

    CHECK(dvsr != 57882617207);

    CHECK(57882617207 % dvsr == 0);

}

TEST_CASE("polygon") {

    using pt_t = point<std::int32_t>;
    using plygn_t = polygon<std::int32_t>;

    constexpr double EPS = 1e-8;

    plygn_t plygn_1(3);
    const std::vector<pt_t> vtxs({pt_t(2, 0), pt_t(0, 2), pt_t(-2, 0), pt_t(0, -2)});

    plygn_1[1] = pt_t(1, 0);
    plygn_1[2] = pt_t(0, 1);

    CHECK(plygn_1.area() == 1);

    CHECK(std::abs(plygn_1.perim() - (2 + std::sqrt(2))) < EPS);

    CHECK(plygn_1.size() == 3);

    const plygn_t plygn_2(std::begin(vtxs), std::end(vtxs));

    CHECK(plygn_2.area() == 16);

    CHECK(std::abs(plygn_2.perim() - (2 * std::sqrt(2)) * 4) < EPS);

    CHECK(plygn_2.size() == 4);

    CHECK(plygn_2.contains(pt_t()) == 1);
    CHECK(plygn_2.contains(pt_t(3, 0)) == 0);
    CHECK(plygn_2.contains(pt_t(2, 2)) == 0);
    CHECK(plygn_2.contains(pt_t(-2, 0)) == 2);
    CHECK(plygn_2.contains(pt_t(-1, 1)) == 2);

}

TEST_CASE("prefix_function") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abcabcd");

    CHECK(prefix_function(std::begin(str), std::end(str)) == vec_t({0, 0, 0, 1, 2, 3, 0}));

    str.assign("aabaaab");

    CHECK(prefix_function(std::begin(str), std::end(str)) == vec_t({0, 1, 0, 1, 2, 2, 3}));

}

TEST_CASE("range_table") {

    using node_t = std::array<std::int32_t, 2>;

    using init_t = std::pair<node_t, std::int32_t>;

    CHECK(range_table::log_2(11) == 3);
    CHECK(range_table::log_2(32) == 5);

    std::queue<init_t> inits;
    std::queue<node_t> nodes;

    inits.emplace(node_t({0, 0}), 1);
    inits.emplace(node_t({0, 1}), 1);
    inits.emplace(node_t({0, 2}), 1);
    inits.emplace(node_t({0, 3}), 1);

    inits.emplace(node_t({1, 0}), 1);
    inits.emplace(node_t({1, 1}), 1);
    inits.emplace(node_t({1, 2}), 1);
    inits.emplace(node_t({1, 3}), 1);

    inits.emplace(node_t({2, 1}), 1);
    inits.emplace(node_t({2, 0}), 0);
    inits.emplace(node_t({2, 2}), 1);
    inits.emplace(node_t({2, 3}), 0);

    range_table::for_all(
        4,
        [&](std::int32_t lvl, std::int32_t idx, std::int32_t rst) -> void {
            const auto [node, cur_rst] = inits.front();
            if (lvl == node[0] && idx == node[1] && rst == cur_rst) {
                inits.pop();
            }
        }
    );

    CHECK(std::empty(inits));

    nodes.push(node_t({2, 1}));
    nodes.push(node_t({2, 3}));

    const auto pop = [&](std::int32_t lvl, std::int32_t idx) -> void {
        if (lvl == nodes.front()[0] && idx == nodes.front()[1]) {
            nodes.pop();
        }
    };

    range_table::for_rng(1, 4, pop);

    CHECK(std::empty(nodes));

    nodes.push(node_t({0, 1}));

    range_table::for_rng(1, 2, pop);

    CHECK(std::empty(nodes));

}

TEST_CASE("segment") {

    using pt_t = point<std::int32_t>;
    using seg_t = segment<std::int32_t>;

    constexpr double EPS = 1e-8;

    const seg_t seg(pt_t(4, 0), pt_t(0, 2));

    CHECK(!seg_t::intersects(seg, seg_t(pt_t(2, -2), pt_t(-2, 2))));
    CHECK(seg_t::intersects(seg, seg_t(pt_t(-2, -1), pt_t(0, 2))));
    CHECK(seg_t::intersects(seg, seg_t(pt_t(), pt_t(2, 2))));

    CHECK(std::abs(seg.length() - std::sqrt(20)) < EPS);

    CHECK(seg.norm() == 20);

}

TEST_CASE("segment_tree") {

    CHECK(segment_tree::log_2(11) == 3);
    CHECK(segment_tree::log_2(32) == 5);

    std::queue<std::int32_t> nds;

    nds.push(1);
    nds.push(3);
    nds.push(6);

    const auto pop = [&](std::int32_t nd) -> void {
        if (nds.front() == nd) {
            nds.pop();
        }
    };

    segment_tree::for_pars(13, 0, pop);

    CHECK(std::empty(nds));

    nds.push(6);
    nds.push(3);
    nds.push(1);

    segment_tree::for_pars(13, 1, pop);

    CHECK(std::empty(nds));

    nds.push(9);
    nds.push(12);
    nds.push(5);

    segment_tree::for_rng(9, 13, pop);

    CHECK(std::empty(nds));

    nds.push(9);
    nds.push(5);
    nds.push(12);

    segment_tree::for_rng_ord(9, 13, pop);

    CHECK(std::empty(nds));

}

TEST_CASE("sequence_hasher") {

    using hshr_t = sequence_hasher<modular_integer<998244353>>;

    hshr_t hshr_1;
    const std::string str("abca");

    hshr_1.push('a');
    hshr_1.push('a');

    CHECK(hshr_1.query(0, 1) == hshr_1.query(1, 2));

    hshr_1.pop();

    hshr_1.push('b');
    hshr_1.push('c');
    hshr_1.push('a');

    CHECK(hshr_1.query(0, 1) != hshr_1.query(1, 2));
    CHECK(hshr_1.query(0, 1) != hshr_1.query(1, 3));
    CHECK(hshr_1.query(0, 1) == hshr_1.query(3, 4));

    hshr_t hshr_2(std::begin(str), std::end(str));

    CHECK(hshr_1.query(0, 1) != hshr_2.query(1, 2));
    CHECK(hshr_1.query(0, 1) != hshr_2.query(1, 3));
    CHECK(hshr_1.query(0, 1) == hshr_2.query(3, 4));

    CHECK(hshr_t::hash(std::begin(str), std::end(str)) == hshr_1.query(0, 4));

}

TEST_CASE("sieve") {

    sieve::reserve(50);

    CHECK(sieve::facts[2] == 2);
    CHECK(sieve::facts[5] == 5);
    CHECK(sieve::facts[9] == 3);
    CHECK(sieve::facts[13] == 13);
    CHECK(sieve::facts[21] == 3);
    CHECK(sieve::facts[25] == 5);
    CHECK(sieve::facts[31] == 31);
    CHECK(sieve::facts[49] == 7);

    CHECK(
        sieve::primes == std::vector<std::int32_t>(
            {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}
        )
    );

}

TEST_CASE("suffix_array") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("abaab");

    CHECK(suffix_array(std::begin(str), std::end(str)) == vec_t({2, 0, 3, 1, 4}));

    str.assign("dcafac ");

    CHECK(suffix_array(std::begin(str), std::end(str)) == vec_t({6, 4, 2, 5, 1, 0, 3}));

}

TEST_CASE("suffix_automaton") {

    using mp_t = std::map<char, std::int32_t>;
    using vec_t = std::vector<std::int32_t>;

    suffix_automaton<char> sa(2);

    sa.extend('a');
    sa.extend('a');

    CHECK(sa.lens == vec_t({0, 1, 2, 0}));
    CHECK(sa.adj[0] == mp_t({std::make_pair('a', 1)}));
    CHECK(sa.adj[1] == mp_t({std::make_pair('a', 2)}));
    CHECK(sa.adj[2] == mp_t());
    CHECK(sa.links == vec_t({-1, 0, 1, 0}));
    CHECK(sa.idx == 3);

    sa = suffix_automaton<char>(3);

    sa.extend('a');
    sa.extend('b');
    sa.extend('a');

    CHECK(sa.lens == vec_t({0, 1, 2, 3, 0, 0}));
    CHECK(sa.adj[0] == mp_t({std::make_pair('a', 1), std::make_pair('b', 2)}));
    CHECK(sa.adj[1] == mp_t({std::make_pair('b', 2)}));
    CHECK(sa.adj[2] == mp_t({std::make_pair('a', 3)}));
    CHECK(sa.adj[3] == mp_t());
    CHECK(sa.links == vec_t({-1, 0, 0, 1, 0, 0}));
    CHECK(sa.idx == 4);

}

TEST_CASE("treap") {

    std::int32_t nxt = 0;
    std::int32_t rt = -1;
    treap trp(6);

    const auto pull = [&](std::int32_t nd) -> void {
        trp.szs[nd] = 1;
        if (trp.nds_l[nd] != -1) {
            trp.szs[nd] += trp.szs[trp.nds_l[nd]];
        }
        if (trp.nds_r[nd] != -1) {
            trp.szs[nd] += trp.szs[trp.nds_r[nd]];
        }
    };
    const auto push = [](std::int32_t) -> void {};

    const auto merge = [&](std::int32_t nd_l, std::int32_t nd_r) -> std::int32_t {
        return trp.merge(nd_l, nd_r, pull, push);
    };
    const auto split = [&](std::int32_t nd, std::int32_t rnk) -> treap::ret_t {
        return trp.split(
            nd,
            [&](std::int32_t nd) -> bool {
                const std::int32_t sz = trp.nds_l[nd] != -1 ? trp.szs[trp.nds_l[nd]] : 0;
                if (sz < rnk) {
                    rnk -= sz + 1;
                    return true;
                } else {
                    return false;
                }
            }, pull, push
        );
    };

    for (std::int32_t i = 0; i < 6; ++i) {
        rt = merge(rt, trp.insert());
    }

    y_combinator(
        [&](auto self, std::int32_t nd) -> void {
            if (trp.nds_l[nd] != -1) {
                self(trp.nds_l[nd]);
            }
            CHECK(nd == nxt);
            ++nxt;
            if (trp.nds_r[nd] != -1) {
                self(trp.nds_r[nd]);
            }
        }
    )(rt);

    CHECK(trp.idx == 6);
    CHECK(nxt == 6);

    const auto [nd_l, nd_r] = split(rt, 4);

    const auto [splt_l, splt_r] = split(nd_l, 1);

    CHECK(trp.szs[splt_l] == 1);
    CHECK(trp.szs[splt_r] == 3);
    CHECK(trp.szs[nd_r] == 2);

    rt = merge(merge(splt_l, splt_r), nd_r);

    CHECK(trp.szs[rt] == 6);

}

TEST_CASE("two_sat") {

    two_sat slvr(3);

    slvr.add(0, 1, 1, 0);
    slvr.add(0, 0, 1, 1);
    slvr.add(0, 1, 1, 1);
    slvr.add(0, 0, 2, 1);

    auto res = slvr.solve();

    CHECK(res);

    bool val = (*res)[0] || !(*res)[1];

    CHECK(val);

    val = !(*res)[0] || (*res)[1];

    CHECK(val);

    val = !(*res)[0] || !(*res)[1];

    CHECK(val);

    val = (*res)[0] || !(*res)[2];

    CHECK(val);

    slvr = two_sat(2);

    slvr.add(0, 0, 1, 0);
    slvr.add(0, 0, 1, 1);
    slvr.add(0, 1, 1, 0);
    slvr.add(0, 1, 1, 1);

    CHECK(!slvr.solve());

}

TEST_CASE("xor_basis") {

    xor_basis<std::uint32_t> basis(4);

    basis.insert(3);

    CHECK(basis.dim() == 1);

    basis.insert(1);

    CHECK(basis.query(0));
    CHECK(basis.query(2));
    CHECK(!basis.query(4));

    basis.insert(4);

    CHECK(basis.query(4));
    CHECK(basis.query(6));
    CHECK(!basis.query(12));

    basis.insert(7);

    CHECK(basis.dim() == 3);

}

TEST_CASE("y_combinator") {

    const auto gcd = y_combinator(
        [&](auto self, std::int32_t m, std::int32_t n) -> std::int32_t {
            return n ? self(n, m % n) : m;
        }
    );

    CHECK(gcd(18, 42) == std::gcd(18, 42));
    CHECK(gcd(64, 127) == std::gcd(64, 127));

}

TEST_CASE("z_function") {

    using vec_t = std::vector<std::int32_t>;

    std::string str("aaaaa");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 4, 3, 2, 1}));

    str.assign("aaabaab");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 2, 1, 0, 2, 1, 0}));

    str.assign("abacaba");

    CHECK(z_function(std::begin(str), std::end(str)) == vec_t({0, 0, 1, 0, 3, 0, 1}));

}
