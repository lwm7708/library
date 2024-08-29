#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <deque>
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
#include "data_structure/range_table.cpp"
#include "data_structure/segment_tree.cpp"
#include "graph/dinic.cpp"
#include "hashing/integral_hash.cpp"
#include "math/algebra/diophantine.cpp"
#include "math/algebra/matrix.cpp"
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
#include "sequence/manacher.cpp"
#include "sequence/prefix_function.cpp"
#include "sequence/sequence_hasher.cpp"
#include "sequence/suffix_array.cpp"
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

TEST_CASE("combinatorics") {

    combinatorics<modular_integer<53>> comb;

    CHECK(comb.combine(8, 3).val == 3);
    CHECK(comb.combine(51, 8).val == 9);

    CHECK(comb.get_fact(8).val == 40);
    CHECK(comb.get_fact(51).val == 1);

    CHECK(comb.get_inv(8).val == 20);
    CHECK(comb.get_inv(51).val == 26);

    CHECK(comb.get_inv_fact(8).val == 4);
    CHECK(comb.get_inv_fact(51).val == 1);

    CHECK(comb.permute(8, 3).val == 18);
    CHECK(comb.permute(51, 8).val == 42);

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

    CHECK(!ntwk.get_side(0));
    CHECK(!ntwk.get_side(1));
    CHECK(!ntwk.get_side(2));
    CHECK(ntwk.get_side(3));
    CHECK(ntwk.get_side(4));
    CHECK(ntwk.get_side(5));

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

TEST_CASE("fenwick_tree") {

    using opt_t = std::pair<std::int32_t, bool>;

    std::queue<std::int32_t> nodes;
    std::queue<opt_t> opts;

    opts.emplace(8, false);
    opts.emplace(4, true);
    opts.emplace(6, false);
    opts.emplace(5, true);

    CHECK(
        fenwick_tree::for_lvls(
            9,
            [&](std::int32_t node) -> bool {
                const auto [c_node, opt] = opts.front();
                if (c_node == node) {
                    opts.pop();
                }
                return opt;
            }
        ) == 5
    );

    CHECK(std::empty(opts));

    nodes.push(3);
    nodes.push(4);
    nodes.push(8);

    const auto pop = [&](std::int32_t node) -> void {
        if (node == nodes.front()) {
            nodes.pop();
        }
    };

    fenwick_tree::for_pars(2, 8, pop);

    CHECK(std::empty(nodes));

    nodes.push(6);
    nodes.push(4);

    fenwick_tree::for_rng(6, pop);

    CHECK(std::empty(nodes));

}

TEST_CASE("integral_hash") {

    const integral_hash hshr;

    CHECK(hshr(33) != hshr(89));
    CHECK(hshr(33) != hshr(-23));
    CHECK(hshr(33) == hshr(33));

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

    CHECK(pt_1.quadrant() == 4);
    CHECK(pt_2.quadrant() == 1);

    CHECK(pt_t().quadrant() == 0);
    CHECK(pt_t(-5, 0).quadrant() == 3);

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

    CHECK(std::abs(plygn_1.perimeter() - (2 + std::sqrt(2))) < EPS);

    CHECK(plygn_1.size() == 3);

    const plygn_t plygn_2(std::begin(vtxs), std::end(vtxs));

    CHECK(plygn_2.area() == 16);

    CHECK(std::abs(plygn_2.perimeter() - (2 * std::sqrt(2)) * 4) < EPS);

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

    using init_t = std::pair<node_t, bool>;

    CHECK(range_table::log_2(11) == 3);
    CHECK(range_table::log_2(32) == 5);

    std::queue<init_t> inits;
    std::queue<node_t> nodes;

    inits.emplace(node_t({0, 0}), true);
    inits.emplace(node_t({0, 1}), true);
    inits.emplace(node_t({0, 2}), true);
    inits.emplace(node_t({0, 3}), true);

    inits.emplace(node_t({1, 0}), true);
    inits.emplace(node_t({1, 1}), true);
    inits.emplace(node_t({1, 2}), true);
    inits.emplace(node_t({1, 3}), true);

    inits.emplace(node_t({2, 1}), true);
    inits.emplace(node_t({2, 0}), false);
    inits.emplace(node_t({2, 2}), true);
    inits.emplace(node_t({2, 3}), false);

    range_table::for_all(
        4,
        [&](std::int32_t lvl, std::int32_t idx, bool rst) -> void {
            const auto [node, c_rst] = inits.front();
            if (lvl == node[0] && idx == node[1] && rst == c_rst) {
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

    using opt_t = std::pair<std::int32_t, bool>;

    std::queue<std::int32_t> nodes;
    std::queue<opt_t> opts;

    opts.emplace(1, false);
    opts.emplace(2, true);
    opts.emplace(5, true);

    const auto pop_node = [&](std::int32_t node) -> void {
        if (nodes.front() == node) {
            nodes.pop();
        }
    };
    const auto pop_opt = [&](std::int32_t node) -> bool {
        const auto [c_node, opt] = opts.front();
        if (node == c_node) {
            opts.pop();
        }
        return opt;
    };

    CHECK(segment_tree::for_lvls(1, 8, false, pop_opt) == 11);

    CHECK(std::empty(opts));

    opts.emplace(1, false);
    opts.emplace(3, false);
    opts.emplace(7, true);

    CHECK(segment_tree::for_lvls(1, 8, true, pop_opt) == 14);

    CHECK(std::empty(opts));

    nodes.push(1);
    nodes.push(3);
    nodes.push(6);

    segment_tree::for_pars(13, false, pop_node);

    CHECK(std::empty(nodes));

    nodes.push(6);
    nodes.push(3);
    nodes.push(1);

    segment_tree::for_pars(13, true, pop_node);

    CHECK(std::empty(nodes));

    nodes.push(9);
    nodes.push(12);
    nodes.push(5);

    segment_tree::for_rng(9, 13, pop_node);

    CHECK(std::empty(nodes));

    nodes.push(9);
    nodes.push(5);
    nodes.push(12);

    segment_tree::for_rng_ord(9, 13, false, pop_node);

    CHECK(std::empty(nodes));

    nodes.push(12);
    nodes.push(5);
    nodes.push(9);

    segment_tree::for_rng_ord(9, 13, true, pop_node);

    CHECK(std::empty(nodes));

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
