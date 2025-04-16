// Author: anksilae@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include <iostream>

namespace graph {

/// **BFS Algorithm**
Graph Algorithms::bfs(Graph& g, int start) {
    int n = g.getNumVertices();

    bool* visited = new bool[n]{false};
    int* discoveryOrder = new int[n];
    int* parent = new int[n];
    int* parentWeight = new int[n]; 

    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        parentWeight[i] = 0;
    }

    int discoveryIndex = 0;

    Queue queue(n); 

    for (int i = 0; i < n; ++i) {
        int root = (i == 0) ? start : i;

        if (!visited[root]) {
            visited[root] = true;
            queue.push(root);

            while (!queue.isEmpty()) {
                int node = queue.pop();
                discoveryOrder[discoveryIndex++] = node;

                // מעבר על השכנים
                Graph::Node* curr = g.getAdjacencyList()[node];
                while (curr) {
                    int neighbor = curr->vertex;
                    int weight = curr->weight;

                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        parent[neighbor] = node;
                        parentWeight[neighbor] = weight;
                        queue.push(neighbor);
                    }

                    curr = curr->next;
                }
            }
        }
    }


    Graph bfsTree(n);
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            bfsTree.addDirectedEdge(parent[i], i, parentWeight[i]);
        }
    }

    bfsTree.setDiscoveryOrder(discoveryOrder);
    bfsTree.setParentArray(parent);
   

    delete[] visited;
    delete[] discoveryOrder;
    delete[] parent;
    delete[] parentWeight;

    return bfsTree;
}


Graph Algorithms::dfs(Graph& g, int start) {
    int n = g.getNumVertices();

    bool* visited = new bool[n]{false};
    int* discoveryOrder = new int[n];
    int* parent = new int[n];
    int* parentWeight = new int[n]; 

    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        parentWeight[i] = 0;
    }

    int discoveryIndex = 0;
    Stack stack(n);

    for (int i = 0; i < n; ++i) {
        int root = (i == 0) ? start : i;
        if (!visited[root]) {
            stack.push(root);

            while (!stack.isEmpty()) {
                int node = stack.pop();
                if (!visited[node]) {
                    visited[node] = true;
                    discoveryOrder[discoveryIndex++] = node;

   
                    int count = 0;
                    Graph::Node* curr = g.getAdjacencyList()[node];
                while (curr) {
                        count++;
                        curr = curr->next;
                    }

              
                    int* neighbors = new int[count];
                    int* weights = new int[count];
                    Graph::Node* curr2 = g.getAdjacencyList()[node];
                    int idx = 0;
                    while (curr2) {
                        neighbors[idx] = curr2->vertex;
                        weights[idx] = curr2->weight;
                        idx++;
                        curr2 = curr2->next;
                    }

                 
                    for (int j = count - 1; j >= 0; j--) {
                        int v = neighbors[j];
                        int w = weights[j];
                        if (!visited[v]) {
                            parent[v] = node;
                            parentWeight[v] = w;
                            stack.push(v);
                        }
                    }
        
                    delete[] neighbors;
                    delete[] weights;
                }
            }
        }
    }

    Graph dfsTree(n);
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            dfsTree.addDirectedEdge(parent[i], i, parentWeight[i]);
        }
    }

    dfsTree.setDiscoveryOrder(discoveryOrder);
    dfsTree.setParentArray(parent);

    delete[] visited;
    delete[] discoveryOrder;
    delete[] parent;
    delete[] parentWeight;

    return dfsTree;
}



Graph Algorithms ::dijkstra(Graph& g, int start) {
    // 1. בדיקה מקדימה לצלעות שליליות
    if (g.isNegative()) {
        throw std::invalid_argument("Dijkstra's algorithm cannot be used with negative edge weights.");
    }

    int n = g.getNumVertices();
    int* distances = new int[n];
    int* parent = new int[n]; // נשמור מי 'ההורה' של כל צומת במסלול הקצר

    // 2. אתחול
    for (int i = 0; i < n; ++i) {
        distances[i] = 1e9;  // "אינסוף"
        parent[i] = -1;      // אין הורה בהתחלה
    }

    Graph dijkstraTree(n);  // זה הגרף שנחזיר בסוף (עץ המסלולים)
    PriorityQueue pq(n);    // תור עדיפויות למימוש ExtractMin

    distances[start] = 0;   // מרחק הצומת ההתחלתי = 0
    pq.insert(start, 0);    // מכניסים את הצומת ההתחלתי עם עדיפות 0

    // 3. הלולאה הראשית של דייקסטרה
    while (!pq.isEmpty()) {
        int node = pq.extractMin(); // הצומת בעל המרחק הקטן ביותר

        // ריצה על כל שכני הצומת (node)
        Graph::Node* current = g.getAdjacencyList()[node];
        while (current) {
            int neighbor = current->vertex;
            int newDist = distances[node] + current->weight;

            // 4. "פעולת ההרפיה" (Relaxation)
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                parent[neighbor] = node;  // 'node' נהיה ההורה של neighbor במסלול הקצר
                pq.insert(neighbor, newDist);
            }
            current = current->next;
        }
    }

    // 5. בניית עץ המסלולים מקודקודי הורה (parent)
    for (int i = 0; i < n; ++i) {
        if (parent[i] != -1) {
            // מוצאים את המשקל המדויק של הקשת parent[i] -> i בגרף המקורי
            Graph::Node* curr = g.getAdjacencyList()[parent[i]];
            while (curr) {
                if (curr->vertex == i) {
                    // מאחר שאנחנו רוצים עץ *מכוון* מההורה אל הילד,
                    // נשתמש ב-addDirectedEdge (אפילו שהגרף המקורי לא מכוון).
                    dijkstraTree.addDirectedEdge(parent[i], i, curr->weight);
                    break;
                }
                curr = curr->next;
            }
        }
    }

    delete[] distances;
    delete[] parent;
    return dijkstraTree;
}

/// **Prim’s Algorithm**
Graph Algorithms::prim(Graph& g, int start) {
    int n = g.getNumVertices();
    bool* inMST = new bool[n]{false};      // סימון אילו צמתים כבר בעץ
    int* key = new int[n];                 // key[v] = משקל הקשת הכי זולה אל v
    int* parent = new int[n];              // parent[v] = ממי הגענו אל v

    for (int i = 0; i < n; ++i) {
        key[i] = 1e9;
        parent[i] = -1;
    }

    key[start] = 0;
    PriorityQueue pq(n);
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        inMST[u] = true;

        // עובר על כל השכנים של u
        Graph::Node* current = g.getAdjacencyList()[u];
        while (current) {
            int v = current->vertex;
            int weight = current->weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.insert(v, key[v]);  // או decreaseKey אם הוא כבר בפנים
            }

            current = current->next;
        }
    }

    // בניית עץ ה-MST מהמידע שנצבר ב-parent[]
    Graph mst(n);
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            // מוצא את המשקל המתאים
            Graph::Node* node = g.getAdjacencyList()[parent[v]];
            while (node) {
                if (node->vertex == v) {
                    mst.addEdge(parent[v], v, node->weight);
                    break;
                }
                node = node->next;
            }
        }
    }

    delete[] inMST;
    delete[] key;
    delete[] parent;
    return mst;
}

Graph Algorithms::kruskal(Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    UnionFind uf(n);

    // אוספים את כל הצלעות לתוך מערך של שלישיות [src, dst, weight]
    int* edgesArray = nullptr;
    int numEdges;
    g.getEdges(&edgesArray, numEdges);

    // אם אין צלעות, אין מה לעבד
    if (edgesArray == nullptr || numEdges == 0) {
        return mst;
    }

    // ממיינים את הצלעות לפי משקל (Selection Sort להדגמה)
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

    // עיבוד הצלעות מהקל לכבד
    for (int i = 0; i < numEdges; i++) {
        int u = edgesArray[i * 3];
        int v = edgesArray[i * 3 + 1];
        int w = edgesArray[i * 3 + 2];

        // אם u ו-v לא באותה קבוצה, מחברים אותם ב-MST ומאחדים קבוצות
        if (uf.find(u) != uf.find(v)) {
            uf.unionSet(u, v);
            mst.addEdge(u, v, w);
        }
    }

    delete[] edgesArray;
    return mst;
}



}
