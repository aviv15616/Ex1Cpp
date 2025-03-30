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

    void removeNode(int from, int toRemove);

public:
    Graph(int vertices);
    ~Graph();
    
    void addEdge(int src, int dst, int weight);
    void removeEdge(int src, int dst);
    void printGraph();
    bool isEdgeExist(int src, int dst);
    
    int getNumEdges() const; 
    void getEdges(int** edgesArray, int& numEdges) const; 

    Node** getAdjacencyList() const { return adjList; }
    int getNumVertices() const { return numVertices; }
};

}

#endif
