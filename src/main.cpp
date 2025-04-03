#include "Graph.h"
#include "Algorithms.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "UnionFind.h"
#include <iostream>

using namespace graph;

void testGraph(Graph& g) {
    std::cout << "\n===== Graph Construction & Printing =====\n";

    g.printGraph();
}

void testBFS_DFS(Graph& g) {
    std::cout << "\n===== BFS Traversal from Node 0 =====\n";
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.printGraph();

    std::cout << "\n===== DFS Traversal from Node 0\n";
    Graph dfsTree = Algorithms::dfs(g, 0); 
    dfsTree.printGraph();
}
void testPrim(Graph& g) {
    std::cout << "\n===== Prim's MST =====\n";
    Graph mst = Algorithms::prim(g, 0);
    bool empty = true;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
    if (mst.getAdjacencyList()[i] != nullptr) {
        empty = false;
        break;
             }
            }
        if (empty) {
          std::cout << "⚠️  MST is empty – no edges added.\n";
        } else {
       std::cout << "✅ MST was built successfully.\n";
        mst.printGraph();
        }

         
}

void testDijkstra(Graph& g) {
    std::cout << "\n===== Dijkstra's Algorithm from Node 0 =====\n";
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.printGraph();
}

void testKruskal(Graph& g) {
    std::cout << "\n===== Kruskal's MST =====\n";
    Graph mst = Algorithms::kruskal(g);

    bool empty = true;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
        if (mst.getAdjacencyList()[i] != nullptr) {
            empty = false;
            break;
        }
    }

    if (empty) {
        std::cout << "⚠️  MST is empty – no edges added.\n";
    } else {
        std::cout << "✅ MST was built successfully.\n";
        mst.printGraph();
    }
}


void testQueue() {
    std::cout << "\n===== Testing Queue =====\n";
    Queue q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    std::cout << "Dequeued: " << q.pop() << "\n";
    std::cout << "Dequeued: " << q.pop() << "\n";
}

void testPriorityQueue() {
    std::cout << "\n===== Testing PriorityQueue =====\n";
    PriorityQueue pq(5);
    pq.insert(1, 50);
    pq.insert(2, 30);
    pq.insert(3, 20);
    pq.decreaseKey(2, 10);  // Fix: Ensure key exists before decreasing

    std::cout << "Extracted Min: " << pq.extractMin() << "\n";
    std::cout << "Extracted Min: " << pq.extractMin() << "\n";
}

void testUnionFind() {
    std::cout << "\n===== Testing Union-Find =====\n";
    UnionFind uf(5);
    uf.unionSet(0, 1);
    uf.unionSet(1, 2);
    
    std::cout << "Are 0 and 2 connected? " << (uf.isConnected(0, 2) ? "Yes" : "No") << "\n";
    std::cout << "Are 3 and 4 connected? " << (uf.isConnected(3, 4) ? "Yes" : "No") << "\n";
}

int main() {
    
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);


    testGraph(g);
    testBFS_DFS(g);
    testDijkstra(g);
    testKruskal(g);
    testPrim(g);
    testQueue();
    testPriorityQueue();
    testUnionFind();

    return 0;
}
