#include "Algorithms.h"
#include "Graph.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "UnionFind.h"
#include <iostream>

namespace graph {

/// **BFS Algorithm**
Graph Algorithms::bfs(Graph& g, int start) {
    int n = g.getNumVertices();
    bool* visited = new bool[n]{false};
    Graph bfsTree(n);
    Queue q(n);

    q.push(start);
    visited[start] = true;

    while (!q.isEmpty()) {
        int node = q.pop();
        Graph::Node* current = g.getAdjacencyList()[node];

        while (current) {
            int neighbor = current->vertex;
            if (!visited[neighbor]) {
                bfsTree.addEdge(node, neighbor, current->weight);
                visited[neighbor] = true;
                q.push(neighbor);
            }
            current = current->next;
        }
    }

    delete[] visited;
    return bfsTree;
}

/// **DFS Algorithm**
Graph Algorithms::dfs(Graph& g, int start) {
    int n = g.getNumVertices();
    bool* visited = new bool[n]{false};
    Graph dfsTree(n);
    PriorityQueue pq(n);

    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int node = pq.extractMin();
        if (!visited[node]) {
            visited[node] = true;
            Graph::Node* current = g.getAdjacencyList()[node];

            while (current) {
                if (!visited[current->vertex]) {
                    dfsTree.addEdge(node, current->vertex, current->weight);
                    pq.insert(current->vertex, current->weight);
                }
                current = current->next;
            }
        }
    }

    delete[] visited;
    return dfsTree;
}

/// **Dijkstra’s Algorithm**
Graph Algorithms::dijkstra(Graph& g, int start) {
    int n = g.getNumVertices();
    int* distances = new int[n];
    for (int i = 0; i < n; ++i) distances[i] = 1e9;

    Graph dijkstraTree(n);
    PriorityQueue pq(n);

    distances[start] = 0;
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int node = pq.extractMin();
        Graph::Node* current = g.getAdjacencyList()[node];

        while (current) {
            int neighbor = current->vertex;
            int newDist = distances[node] + current->weight;

            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                dijkstraTree.addEdge(node, neighbor, current->weight);
                pq.decreaseKey(neighbor, newDist);
            }
            current = current->next;
        }
    }

    delete[] distances;
    return dijkstraTree;
}

/// **Prim’s Algorithm**
Graph Algorithms::prim(Graph& g, int start) {
    int n = g.getNumVertices();
    bool* inMST = new bool[n]{false};
    int* minEdge = new int[n];
    for (int i = 0; i < n; ++i) minEdge[i] = 1e9;

    Graph mst(n);
    PriorityQueue pq(n);

    minEdge[start] = 0;
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int node = pq.extractMin();
        inMST[node] = true;
        Graph::Node* current = g.getAdjacencyList()[node];

        while (current) {
            int neighbor = current->vertex;
            if (!inMST[neighbor] && current->weight < minEdge[neighbor]) {
                minEdge[neighbor] = current->weight;
                mst.addEdge(node, neighbor, current->weight);
                pq.insert(neighbor, current->weight);
            }
            current = current->next;
        }
    }

    delete[] inMST;
    delete[] minEdge;
    return mst;
}

/// **Kruskal’s Algorithm**
Graph Algorithms::kruskal(Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    UnionFind uf(n);

    int* edgesArray = nullptr;
    int numEdges;
    g.getEdges(&edgesArray, numEdges);

    if (edgesArray == nullptr || numEdges == 0) {
        return mst;
    }

    // **Optimized Selection Sort for Edges**
    for (int i = 0; i < numEdges - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < numEdges; j++) {
            if (edgesArray[j * 3 + 2] < edgesArray[minIndex * 3 + 2]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            for (int k = 0; k < 3; k++) {
                std::swap(edgesArray[i * 3 + k], edgesArray[minIndex * 3 + k]);
            }
        }
    }

    // **Process Sorted Edges for Kruskal**
    for (int i = 0; i < numEdges; i++) {
        int u = edgesArray[i * 3];
        int v = edgesArray[i * 3 + 1];
        int w = edgesArray[i * 3 + 2];

        if (uf.find(u) != uf.find(v)) {
            uf.unionSet(u, v);
            mst.addEdge(u, v, w);
        }
    }

    delete[] edgesArray;
    return mst;
}


}
