#ifndef GRAPH_H
#define GRAPH_H

namespace graph {

class Graph {
public:
    struct Node {
        int vertex, weight;
        Node* next;
    };

private:
    int numVertices;
    Node** adjList;
    int howManyNegatives;

    int* discoveryOrder;
    int* parent;



    void removeNode(int from, int toRemove);
    bool isEdgeExist(int src, int dst);
    bool isValidEdge(int src, int dst);
    bool isValidVertex(int v) const;
    int getNumEdges() const;
 

public:
    Graph(int vertices);
    ~Graph();

    void addEdge(int src, int dst, int weight);
    void removeEdge(int src, int dst);
    void printGraph();

    void addDirectedEdge(int src, int dst, int weight);
    bool isNegative();
    void getEdges(int** edgesArray, int& numEdges) const;

    void setDiscoveryOrder(int* order);
    const int* getDiscoveryOrder() const { return discoveryOrder; }

    void setParentArray(int* p);
    const int* getParentArray() const { return parent; }


    Node** getAdjacencyList() const { return adjList; }
    int getNumVertices() const { return numVertices; }
};

}

#endif
