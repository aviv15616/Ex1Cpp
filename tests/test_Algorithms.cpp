// Author: anksilae@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <stdexcept>

using namespace graph;

/* ==========================
 *           BFS
 * ========================== */

TEST_CASE("BFS constructs valid tree") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::bfs(g, 0);

    CHECK(tree.getNumVertices() == 4);
    CHECK(tree.getNumEdges() == 3);  // שרשור 0->1->2->3
}

TEST_CASE("BFS on single vertex") {
    Graph g(1);
    // אין צלעות
    Graph tree = Algorithms::bfs(g, 0);

    CHECK(tree.getNumVertices() == 1);
    CHECK(tree.getNumEdges() == 0);
}

TEST_CASE("BFS on disconnected graph") {

    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(2, 3, 20);

    Graph tree = Algorithms::bfs(g, 0);

    // נקבל 'יער' עם 2 עצים: אחד ברכיב 0-1, אחד ברכיב 2-3
    CHECK(tree.getNumVertices() == 4);
    // בכל רכיב יש צלע אחת
    CHECK(tree.getNumEdges() == 2);
}
TEST_CASE("BFS correct discovery order") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    Graph tree = Algorithms::bfs(g, 0);

    int expectedOrder[5] = {0, 1, 2, 3, 4};
    int* order = new int[5];
    tree.getDiscoveryOrder(order);  

    for (int i = 0; i < 5; ++i) {
        CHECK(order[i] == expectedOrder[i]);
    }

    delete[] order;
}





/* ==========================
 *           DFS
 * ========================== */

TEST_CASE("DFS constructs valid tree") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);

    Graph tree = Algorithms::dfs(g, 0);

    CHECK(tree.getNumVertices() == 5);
    CHECK(tree.getNumEdges() == 4); // DFS builds a tree with n-1 edges
}

TEST_CASE("DFS on single vertex") {
    Graph g(1);
    Graph tree = Algorithms::dfs(g, 0);

    CHECK(tree.getNumVertices() == 1);
    CHECK(tree.getNumEdges() == 0);
}

TEST_CASE("DFS on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(2, 3, 20);

    Graph tree = Algorithms::dfs(g, 0);

    CHECK(tree.getNumVertices() == 4);
    CHECK(tree.getNumEdges() == 2);  // שני רכיבים
}
TEST_CASE("DFS correct discovery order") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);


    Graph tree = Algorithms::dfs(g, 0);

    int* order = new int[5];
    tree.getDiscoveryOrder(order); 
    
    int expectedOrder[5] = {0, 1, 3, 2, 4}; // DFS order

    for (int i = 0; i < 5; ++i) {
        CHECK(order[i] == expectedOrder[i]);
    }

    delete[] order;

}


/* ==========================
 *         Dijkstra
 * ========================== */

TEST_CASE("Dijkstra throws on negative weights") {
    Graph g(3);
    g.addEdge(0, 1, -2);
    CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
}

TEST_CASE("Dijkstra returns shortest paths tree") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getNumVertices() == 5);
    CHECK(tree.getNumEdges() == 4);
}

TEST_CASE("Dijkstra on disconnected graph") {
    // רכיב ראשון: 0--1, שני: 2--3
    // מהצומת 0 לא מגיעים ל-2/3, אז הם יישארו מרחק אינסוף.
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(2, 3, 5);

    Graph result = Algorithms::dijkstra(g, 0);

    CHECK(result.getNumVertices() == 4);
    // בצד של הרכיב של 0 (שהוא 0-1) תהיה צלע אחת,
    // הצומת 2 ו-3 לא נגישים, אז אין צלעות עבורם.
    CHECK(result.getNumEdges() == 1);
}


TEST_CASE("Dijkstra with negative edges") {
    // Dijkstra לא יכול להתמודד עם שליליים (זורקת חריגה)
    Graph g(3);
    g.addEdge(0, 1, -2);
    g.addEdge(1, 2, 1);

    CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
}

TEST_CASE("Dijkstra on single vertex") {
    Graph g(1);
    // אין צלעות
    Graph tree = Algorithms::dijkstra(g, 0);

    CHECK(tree.getNumVertices() == 1);
    CHECK(tree.getNumEdges() == 0);
}
TEST_CASE("Dijkstra computes shortest paths from node 0") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    Graph result = Algorithms::dijkstra(g, 0);
    CHECK(result.getNumEdges() == 4);  // כל הקודקודים מחוברים לעץ קצר
    CHECK(result.getNumVertices() == 5);

    int* edges = nullptr;
    int numEdges = 0;
    result.getEdges(&edges, numEdges);

    int totalWeight = 0;
    for (int i = 0; i < numEdges; ++i) {
        totalWeight += edges[i * 3 + 2];
    }

    // סכום משקלי הקשתות במסלולים הקצרים: 1+2+1+5 = 9 (שימו לב! זה סה"כ משקלי ההורים, לא סכום מרחקים!)
    CHECK(totalWeight == 9);

    delete[] edges;
}



/* ==========================
 *          Prim
 * ========================== */

TEST_CASE("Prim returns a valid MST") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::prim(g, 0);
    CHECK(tree.getNumVertices() == 4);
    CHECK(tree.getNumEdges() == 3); // MST has n-1 edges
}

TEST_CASE("Prim on single vertex") {
    Graph g(1);
    // אין צלעות
    Graph tree = Algorithms::prim(g, 0);

    CHECK(tree.getNumVertices() == 1);
    CHECK(tree.getNumEdges() == 0);
}

TEST_CASE("Prim on disconnected graph") {
    // רכיב: 0--1, רכיב: 2--3
    // בהנחה שהאלגוריתם לא מותאם לכתוב MST לכל הגרף,
    // הוא יתמקד רק ברכיב של start=0
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(2, 3, 20);

    Graph tree = Algorithms::prim(g, 0);
    // יש רק 2 צמתים ברכיב של 0
    CHECK(tree.getNumVertices() == 4);
    // צלע 0--1 בלבד
    CHECK(tree.getNumEdges() == 1);
}
TEST_CASE("Prim returns correct MST") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    Graph mst = Algorithms::prim(g, 0);
    CHECK(mst.getNumEdges() == 4);  // n - 1
    CHECK(mst.getNumVertices() == 5);

    int* edges = nullptr;
    int numEdges = 0;
    mst.getEdges(&edges, numEdges);

    int totalWeight = 0;
    for (int i = 0; i < numEdges; ++i) {
        totalWeight += edges[i * 3 + 2];
    }

    CHECK(totalWeight == 8);  // סכום המשקלים של MST

    delete[] edges;
}






/* ==========================
 *        Kruskal
 * ========================== */

TEST_CASE("Kruskal returns a valid MST") {
    Graph g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 1);

    Graph tree = Algorithms::kruskal(g);
    CHECK(tree.getNumVertices() == 5);
    CHECK(tree.getNumEdges() == 4);
}



TEST_CASE("Kruskal on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    // אין חיבור בין 0/1 ל-2/3 => נוצר forest
    Graph mst = Algorithms::kruskal(g);

    CHECK(mst.getNumVertices() == 4);
    // יש צלע אחת בכל רכיב
    CHECK(mst.getNumEdges() == 2);
}


TEST_CASE("Kruskal with negative edges") {
    // Kruskal יכול להתמודד עם שליליים (לא נזרקת חריגה בד"כ)
    Graph g(3);
    g.addEdge(0, 1, -2);
    g.addEdge(1, 2, 1);

    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumEdges() == 2); // עדיין מחבר את כולם
}
TEST_CASE("Kruskal returns correct MST") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumEdges() == 4);
    CHECK(mst.getNumVertices() == 5);

    int* edges = nullptr;
    int numEdges = 0;
    mst.getEdges(&edges, numEdges);

    int totalWeight = 0;
    for (int i = 0; i < numEdges; ++i) {
        totalWeight += edges[i * 3 + 2];
    }

    CHECK(totalWeight == 8);  // סכום המשקלים של MST

    delete[] edges;
}

