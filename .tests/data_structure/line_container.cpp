#include <functional>

#include "include/doctest.h"

#include "data_structure/line_container.cpp"

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
