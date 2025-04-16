// Author: anksilae@gmail.com

#include "doctest.h"
#include "Queue.hpp"
#include <stdexcept>

TEST_CASE("Queue basic operations") {
    Queue q(3);

    CHECK(q.isEmpty());
    q.push(1);
    q.push(2);
    CHECK(!q.isEmpty());

    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue overflow and underflow") {
    Queue q(2);

    q.push(10);
    q.push(20);
    CHECK_THROWS_AS(q.push(30), std::overflow_error); // יותר מהקיבולת

    CHECK(q.pop() == 10);
    CHECK(q.pop() == 20);
    CHECK_THROWS_AS(q.pop(), std::underflow_error);   // אין מה להוציא
}

TEST_CASE("Queue circular behavior") {
    Queue q(3);
    q.push(1);
    q.push(2);
    q.pop();       // מסיר 1
    q.pop();       // מסיר 2
    q.push(3);
    q.push(4);
    q.push(5);

    CHECK(q.pop() == 3);
    CHECK(q.pop() == 4);
    CHECK(q.pop() == 5);
    CHECK(q.isEmpty());
}
