#include "include/doctest.h"

#include "data_structure/bitset.cpp"

TEST_CASE("bitset") {

    bitset st_1(4);
    bitset st_2(4);

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

    CHECK(!st_1[0]);
    CHECK(!st_1[1]);
    CHECK(!st_1[2]);
    CHECK(!st_1[3]);

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

    CHECK(st_1.size() == 4);
    CHECK(st_2.size() == 4);

    bitset st_3 = st_1;

    CHECK(st_1 == st_3);
    CHECK(st_1 != st_2);

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
