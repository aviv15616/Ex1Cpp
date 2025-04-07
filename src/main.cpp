// Author: anksilae@gmail.com
// Demo file to showcase the main functionalities of graph structures & algorithms

#include "Graph.hpp"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include "Stack.hpp"
#include <iostream>

using namespace graph;

void showGraph(Graph &g) {
    std::cout << "\n🔹 Graph structure:\n";
    g.printGraph();
}

void showBFS(Graph &g) {
    std::cout << "\n🔹 BFS from node 0:\n";
    Graph bfs = Algorithms::bfs(g, 0);
    bfs.printGraph();
}

void showDFS(Graph &g) {
    std::cout << "\n🔹 DFS from node 0:\n";
    Graph dfs = Algorithms::dfs(g, 0);
    dfs.printGraph();
}

void showPrim(Graph &g) {
    std::cout << "\n🔹 Prim's MST:\n";
    Graph mst = Algorithms::prim(g, 0);
    mst.printGraph();
}

void showDijkstra(Graph &g) {
    std::cout << "\n🔹 Dijkstra from node 0:\n";
    Graph dijkstra = Algorithms::dijkstra(g, 0);
    dijkstra.printGraph();
}

void showKruskal(Graph &g) {
    std::cout << "\n🔹 Kruskal's MST:\n";
    Graph mst = Algorithms::kruskal(g);
    mst.printGraph();
}

void demoQueue() {
    std::cout << "\n🔹 Queue operations:\n";
    Queue q(5);

    std::cout << "🟢 Enqueuing 10...\n";
    q.push(10);
    q.print();

    std::cout << "🟢 Enqueuing 20...\n";
    q.push(20);
    q.print();

    std::cout << "🟢 Enqueuing 30...\n";
    q.push(30);
    q.print();

    std::cout << "🔴 Dequeuing...\n";
    std::cout << "Popped: " << q.pop() << "\n";
    q.print();

    std::cout << "🔴 Dequeuing...\n";
    std::cout << "Popped: " << q.pop() << "\n";
    q.print();
}

void demoPriorityQueue() {
    std::cout << "\n🔹 PriorityQueue operations:\n";
    PriorityQueue pq(5);
    pq.insert(1, 50);
    pq.insert(2, 30);
    pq.insert(3, 20);
    std::cout << "Priority queue after inserts: ";
    pq.print();
    pq.decreaseKey(2, 10);
    std::cout << "After decreaseKey(2,10): ";
    pq.print();
    std::cout << "Extracted Min: " << pq.extractMin() << "\n";
    std::cout << "Extracted Min: " << pq.extractMin() << "\n";
    std::cout << "Priority queue after extractions: ";
    pq.print();
}

void demoUnionFind() {
    std::cout << "\n🔹 Union-Find operations:\n";
    UnionFind uf(5);

    std::cout << "Initial connected sets:\n";
    uf.print();

    uf.unionSet(0, 1);
    std::cout << "After union(0,1):\n";
    uf.print();

    uf.unionSet(1, 2);
    std::cout << "After union(1,2):\n";
    uf.print();

    std::cout << (uf.isConnected(0, 2) ? "0 ↔ 2? Yes\n" : "0 ↔ 2? No\n");
    std::cout << (uf.isConnected(3, 4) ? "3 ↔ 4? Yes\n" : "3 ↔ 4? No\n");
}

void demoStack() {
    std::cout << "\n🔹 Stack operations:\n";
    Stack s(5);

    std::cout << "🟢 Pushing 100...\n";
    s.push(100);
    s.print();

    std::cout << "🟢 Pushing 200...\n";
    s.push(200);
    s.print();

    std::cout << "🟢 Pushing 300...\n";
    s.push(300);
    s.print();

    std::cout << "🔴 Popping...\n";
    std::cout << "Popped: " << s.pop() << "\n";
    s.print();

    std::cout << "🔴 Popping...\n";
    std::cout << "Popped: " << s.pop() << "\n";
    s.print();
}


int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5);

    showGraph(g);
    showBFS(g);
    showDFS(g);
    showDijkstra(g);
    showKruskal(g);
    showPrim(g);

    demoQueue();
    demoPriorityQueue();
    demoUnionFind();
    demoStack();

    return 0;
}
