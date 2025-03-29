#include "Graph.h"
#include <iostream>
#include <cassert> // For assertions
#include <stdexcept> // For exception handling

using namespace graph;

// Function Declarations
void testAddEdge();
void testRemoveEdge();
void testPrintGraph();
void testRemoveNode();
void testIsValidEdge();
void testIsEdgeExist();

int main() {
    // Run each test case
    testAddEdge();
    testRemoveEdge();
    testPrintGraph();
    testRemoveNode();
    testIsValidEdge();
    testIsEdgeExist();

    std::cout << "✅ ALL TESTS PASSED SUCCESSFULLY!" << std::endl;
    return 0;
}

// ----------------------------------
// 📌 TEST CASES
// ----------------------------------

// 🔹 Test addEdge() function (correctness + exceptions)
void testAddEdge() {
    Graph g(5);

    // ✅ Valid edge additions
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);

    assert(g.isEdgeExist(0, 1));
    assert(g.isEdgeExist(1, 0));
    assert(g.isEdgeExist(0, 2));
    assert(g.isEdgeExist(2, 0));

    // ❌ Exception 1: Invalid edge (out of bounds)
    try {
        g.addEdge(0, 5, 10); // Vertex 5 is out of range
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "✅ Caught expected exception for out-of-bounds vertex: " << e.what() << std::endl;
    }

    // ❌ Exception 2: Edge already exists
    try {
        g.addEdge(0, 1, 10); // Edge (0,1) already added
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Caught expected exception for adding duplicate edge: " << e.what() << std::endl;
    }

    std::cout << "✅ testAddEdge PASSED!" << std::endl;
}

// 🔹 Test removeEdge() function (correctness + exceptions)
void testRemoveEdge() {
    Graph g(5);

    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 7);

    // ✅ Valid removal
    g.removeEdge(0, 1);
    assert(!g.isEdgeExist(0, 1));
    assert(!g.isEdgeExist(1, 0));

    // ❌ Exception 3: Removing an invalid edge
    try {
        g.removeEdge(0, 1); // Edge (0,1) is already removed
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Caught expected exception for removing non-existent edge: " << e.what() << std::endl;
    }

    // ❌ Exception 4: Removing edge from non-existent vertex
    try {
        g.removeEdge(0, 5); // Vertex 5 doesn't exist
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "✅ Caught expected exception for removing edge with out-of-bounds vertex: " << e.what() << std::endl;
    }

    std::cout << "✅ testRemoveEdge PASSED!" << std::endl;
}

// 🔹 Test printGraph() function (correctness)
void testPrintGraph() {
    Graph g(3);
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 6);

    std::cout << "📌 Expected Graph Output:" << std::endl;
    std::cout << "0 → (1, 4)" << std::endl;
    std::cout << "1 → (2, 6) , (0, 4)" << std::endl;
    std::cout << "2 → (1, 6)" << std::endl;

    std::cout << "📌 Actual Graph Output:" << std::endl;
    g.printGraph(); // Manual check

    std::cout << "✅ testPrintGraph PASSED (manual check)!" << std::endl;
}

// 🔹 Test removeNode() function (correctness + exceptions)
void testRemoveNode() {
    Graph g(3);

    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);

    // ✅ Valid removal
    g.removeEdge(1, 2);
    assert(!g.isEdgeExist(1, 2));
    assert(!g.isEdgeExist(2, 1));

    // ❌ Exception 5: Removing from an empty adjacency list
    try {
        g.removeEdge(2, 0);  // Vertex 2 now has no edges
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Caught expected exception in testRemoveNode: " << e.what() << std::endl;
    }

    // ❌ Exception 6: Removing a non-existent node
    try {
        g.removeNode(0, 3); // Vertex 3 doesn't exist in adjacency list
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Caught expected exception for removing non-existent node: " << e.what() << std::endl;
    }

    std::cout << "✅ testRemoveNode PASSED!" << std::endl;
}

// 🔹 Test isValidEdge() function (correctness + exceptions)
void testIsValidEdge() {
    Graph g(5);

    // ✅ Valid edges
    assert(g.isValidEdge(0, 1));
    assert(g.isValidEdge(3, 4));

    // ❌ Exception cases
    try {
        g.addEdge(2, 2, 10); // Self-loop test
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "✅ Caught expected exception for self-loop: " << e.what() << std::endl;
    }

    try {
        g.addEdge(1, 10, 5); // Out-of-bounds vertex
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "✅ Caught expected exception for out-of-bounds edge: " << e.what() << std::endl;
    }

    std::cout << "✅ testIsValidEdge PASSED!" << std::endl;
}

// 🔹 Test isEdgeExist() function (correctness)
void testIsEdgeExist() {
    Graph g(4);

    g.addEdge(0, 1, 3);
    g.addEdge(1, 2, 7);

    // ✅ Valid edge checks
    assert(g.isEdgeExist(0, 1));
    assert(!g.isEdgeExist(0, 2)); // Edge not added

    // ✅ Check non-existent vertex (instead of expecting an exception)
    assert(!g.isEdgeExist(0, 5)); // Vertex 5 is out of range, should return false

    std::cout << "✅ testIsEdgeExist PASSED!" << std::endl;
}

