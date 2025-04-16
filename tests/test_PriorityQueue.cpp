// Author: anksilae@gmail.com

#include "doctest.h"
#include "PriorityQueue.hpp"
#include <stdexcept>



TEST_CASE("Insert and extractMin - normal flow") {
    PriorityQueue pq(3);

    pq.insert(3, 30);
    pq.insert(1, 10);
    pq.insert(2, 20);

    CHECK(!pq.isEmpty());

    CHECK(pq.extractMin() == 1);  // הקודקוד עם הערך הקטן ביותר (10)
    CHECK(pq.extractMin() == 2);  // הבא בתור
    CHECK(pq.extractMin() == 3);  // האחרון

    CHECK(pq.isEmpty());
}

TEST_CASE("Insert beyond initial capacity") {
    PriorityQueue pq(2);
    pq.insert(1, 100);
    pq.insert(2, 200);
    pq.insert(3, 50);  // צריך לגרום להרחבה דינמית

    CHECK(pq.extractMin() == 3);  // הכי קטן
    CHECK(pq.extractMin() == 1);
    CHECK(pq.extractMin() == 2);
}

TEST_CASE("Decrease key affects order") {
    PriorityQueue pq(5);
    pq.insert(10, 100);
    pq.insert(20, 200);
    pq.insert(30, 300);

    pq.decreaseKey(30, 50);  // הופך את 30 לקטן ביותר
    CHECK(pq.extractMin() == 30);
}

TEST_CASE("Decrease key on nonexistent key does nothing") {
    PriorityQueue pq(3);
    pq.insert(5, 500);
    pq.decreaseKey(99, 1);  // לא קיים, לא יקרה כלום

    CHECK(pq.extractMin() == 5);  // עדיין 5
}

TEST_CASE("Extract from empty queue throws") {
    PriorityQueue pq(2);
    CHECK_THROWS_AS(pq.extractMin(), std::underflow_error);
}

