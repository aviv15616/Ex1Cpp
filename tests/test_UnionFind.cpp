// Author: anksilae@gmail.com

#include "doctest.h"
#include "UnionFind.hpp"

TEST_CASE("UnionFind basic functionality") {
    UnionFind uf(5);

    // בתחילה אף אחד לא מחובר
    CHECK(!uf.isConnected(0, 1));
    CHECK(!uf.isConnected(2, 3));

    // איחוד קבוצה
    uf.unionSet(0, 1);
    CHECK(uf.isConnected(0, 1));

    uf.unionSet(1, 2);
    CHECK(uf.isConnected(0, 2));
    CHECK(uf.isConnected(1, 2));
    CHECK(!uf.isConnected(3, 4));
}

TEST_CASE("UnionFind transitivity") {
    UnionFind uf(6);
    uf.unionSet(0, 1);
    uf.unionSet(1, 2);
    uf.unionSet(2, 3);

    CHECK(uf.isConnected(0, 3));
    CHECK(uf.isConnected(1, 3));
    CHECK(!uf.isConnected(4, 5));

    uf.unionSet(3, 4);
    CHECK(uf.isConnected(0, 4));
}

TEST_CASE("UnionFind self connection") {
    UnionFind uf(3);

    CHECK(uf.isConnected(0, 0));
    CHECK(uf.isConnected(1, 1));

    uf.unionSet(0, 1);
    CHECK(uf.isConnected(0, 1));
    CHECK(uf.isConnected(1, 0));
}
