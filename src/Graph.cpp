#include "Graph.h"
#include <iostream>
#include <stdexcept>

namespace graph {

// **Constructor: Initializes adjacency list**
Graph::Graph(int vertices) : numVertices(vertices), hasNegative(false) {
    if (vertices <= 0) {
        throw std::invalid_argument("Graph must have at least one vertex.");
    }
    adjList = new Node*[numVertices]();
}

// **Destructor: Cleans up allocated memory**
Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        Node* current = adjList[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
}

// **Checks if an edge already exists**
bool Graph::isEdgeExist(int src, int dst) {
    if (src < 0 || src >= numVertices || adjList[src] == nullptr) {
        return false;
    }
    Node* curr = adjList[src];
    while (curr) {
        if (curr->vertex == dst) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// **Adds an edge to the graph (undirected)**
void Graph::addEdge(int src, int dst, int weight) {
    if (src == dst || src < 0 || dst < 0 || src >= numVertices || dst >= numVertices) {
        throw std::out_of_range("Invalid edge");
    }
    if (isEdgeExist(src, dst)) {
        throw std::invalid_argument("Edge already exists.");
    }
    
    // Add edge src -> dst
    Node* newNode = new Node{dst, weight, adjList[src]};
    adjList[src] = newNode;

    // Add edge dst -> src
    newNode = new Node{src, weight, adjList[dst]};
    adjList[dst] = newNode;
    
    if (weight < 0) {
        hasNegative = true;
    }
}

// **New: Adds a directed edge (only one direction)**
void Graph::addDirectedEdge(int src, int dst, int weight) {
    if (src < 0 || dst < 0 || src >= numVertices || dst >= numVertices) {
        throw std::out_of_range("Invalid edge");
    }
    // We don't check for existence here since the dijkstra tree is built in a controlled way.
    Node* newNode = new Node{dst, weight, adjList[src]};
    adjList[src] = newNode;
}

bool Graph::containsNegative(){
    return hasNegative;
}

// **Removes an edge from the graph**
void Graph::removeEdge(int src, int dst) {
    if (src == dst || src < 0 || dst < 0 || src >= numVertices || dst >= numVertices) {
        throw std::out_of_range("Invalid edge");
    }
    if (!isEdgeExist(src, dst)) {
        throw std::invalid_argument("Edge does not exist.");
    }
    removeNode(src, dst);
    removeNode(dst, src);
}

// **Helper function to remove a node from adjacency list**
void Graph::removeNode(int from, int toRemove) {
    if (!adjList[from]) return;
    Node* prev = nullptr;
    Node* curr = adjList[from];
    while (curr) {
        if (curr->vertex == toRemove) {
            if (prev) {
                prev->next = curr->next;
            } else {
                adjList[from] = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// **Prints the graph as an adjacency list**
void Graph::printGraph() {
    for (int i = 0; i < numVertices; i++) {
        if (!adjList[i]) continue;  // **Fix: Skip empty adjacency lists**
        Node* curr = adjList[i];
        std::cout << i << " → ";
        while (curr) {
            std::cout << "(" << curr->vertex << ", " << curr->weight << ")";
            if (curr->next) std::cout << " -> ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

// **Returns the total number of edges (undirected)**
int Graph::getNumEdges() const {
    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        Node* curr = adjList[i];
        while (curr) {
            if (curr->vertex > i) count++; // Avoid counting duplicates
            curr = curr->next;
        }
    }
    return count;
}

// **Retrieves all edges as an array of (src, dst, weight)**
void Graph::getEdges(int** edgesArray, int& numEdges) const {
    numEdges = getNumEdges();
    if (numEdges == 0) {
        *edgesArray = nullptr;
        return;
    }
    *edgesArray = new int[numEdges * 3]; // Store edges as triples (src, dst, weight)
    int index = 0;
    for (int i = 0; i < numVertices; i++) {
        Node* curr = adjList[i];
        while (curr) {
            if (curr->vertex > i) { // Avoid duplicates
                (*edgesArray)[index++] = i; // Source
                (*edgesArray)[index++] = curr->vertex; // Destination
                (*edgesArray)[index++] = curr->weight; // Weight
            }
            curr = curr->next;
        }
    }
}

}  // namespace graph
