// Author: anksilae@gmail.com

#include "doctest.h"
#include "Stack.hpp"
#include <stdexcept>

TEST_CASE("Stack basic operations") {
    Stack s(3);

    CHECK(s.isEmpty());
    s.push(10);
    s.push(20);
    CHECK(!s.isEmpty());

    CHECK(s.pop() == 20);
    CHECK(s.pop() == 10);
    CHECK(s.isEmpty());
}

TEST_CASE("Stack overflow and underflow") {
    Stack s(2);

    s.push(1);
    s.push(2);
    CHECK_THROWS_AS(s.push(3), std::overflow_error); // קיבולת מלאה

    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK_THROWS_AS(s.pop(), std::underflow_error);  // ריק
}

TEST_CASE("Stack push/pop order (LIFO)") {
    Stack s(4);
    s.push(5);
    s.push(10);
    s.push(15);

    CHECK(s.pop() == 15);
    CHECK(s.pop() == 10);
    CHECK(s.pop() == 5);
}
