// Author: anksilae@gmail.com

#include "doctest.h"
#include "Graph.hpp"
#include <stdexcept>
#include <sstream>

using namespace graph;

TEST_CASE("Graph creation") {
    CHECK_THROWS_AS(Graph(0), std::invalid_argument);
    Graph g(3);
    CHECK(g.getNumVertices() == 3);
    CHECK(g.getNumEdges() == 0);
}

TEST_CASE("Edge addition and duplicates") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    CHECK(g.getNumEdges() == 1);
    CHECK_THROWS_AS(g.addEdge(0, 1, 10), std::invalid_argument);
    CHECK_THROWS_AS(g.addEdge(1, 0, 10), std::invalid_argument);
    CHECK_THROWS_AS(g.addEdge(-1, 2, 5), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(2, 2, 5), std::out_of_range);
}

TEST_CASE("Edge removal") {
    Graph g(3);
    g.addEdge(0, 1, 10);
    CHECK(g.getNumEdges() == 1);

    g.removeEdge(0, 1);
    CHECK(g.getNumEdges() == 0);

    CHECK_THROWS_AS(g.removeEdge(0, 1), std::invalid_argument);
}

TEST_CASE("Negative weights and isNegative()") {
    Graph g(3);
    CHECK(!g.isNegative());
    g.addEdge(0, 1, -5);
    CHECK(g.isNegative());
    g.removeEdge(0, 1);
    CHECK(!g.isNegative());
}

TEST_CASE("getEdges() returns correct edges") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 7);

    int* edges = nullptr;
    int numEdges = 0;
    g.getEdges(&edges, numEdges);

    CHECK(numEdges == 2);
    CHECK(edges[0] == 0);
    CHECK(edges[1] == 1);
    CHECK(edges[2] == 5);
    CHECK(edges[3] == 1);
    CHECK(edges[4] == 2);
    CHECK(edges[5] == 7);

    delete[] edges;
}

TEST_CASE("Add and remove self-loop") {
    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(0, 0, 5), std::out_of_range);
}

TEST_CASE("Add edges with invalid vertices") {
    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(0, 3, 5), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(-1, 2, 5), std::out_of_range);
}

TEST_CASE("Graph with one vertex") {
    Graph g(1);
    CHECK(g.getNumVertices() == 1);
    CHECK(g.getNumEdges() == 0);
}

TEST_CASE("Graph with multiple edges and connected components") {
    Graph g(5);
    g.addEdge(0, 1, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(3, 4, 5);

    CHECK(g.getNumEdges() == 3);
}

TEST_CASE("isEdgeExist returns correct value") {
    Graph g(3);
    CHECK(!g.isEdgeExist(0, 1));
    g.addEdge(0, 1, 5);
    CHECK(g.isEdgeExist(0, 1));
    CHECK(g.isEdgeExist(1, 0));
}

TEST_CASE("isValidEdge and isValidVertex") {
    Graph g(3);
    CHECK(g.isValidVertex(0));
    CHECK(!g.isValidVertex(3));
    CHECK(g.isValidEdge(0, 2));
    CHECK(!g.isValidEdge(1, 1));  // self-loop
    CHECK(!g.isValidEdge(0, 5));  // invalid vertex
}
