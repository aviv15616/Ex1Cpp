#ifndef GRAPH_H
#define GRAPH_H

namespace graph {

class Graph {

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int src, int dst, int weight = 1);
    void removeEdge(int src, int dst);
    void printGraph();
    bool isValidEdge(int src, int dst);
    bool isEdgeExist(int src, int dst);
    void removeNode(int from, int toRemove);


private:
    struct Node{
        int neighbor;
        int weight;
        Node* next;
    };

    int numVertices;
    Node ** adjList;


};
}


#endif