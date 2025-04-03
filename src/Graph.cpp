#include "Graph.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace graph {

Graph::Graph(int vertices)
    : numVertices(vertices), howManyNegatives(0),
      discoveryOrder(nullptr), parent(nullptr)
{
    if (vertices <= 0) throw std::invalid_argument("Graph must have at least one vertex.");
    adjList = new Node*[numVertices]();
}

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
    delete[] discoveryOrder;
    delete[] parent;
}

void Graph::addEdge(int src, int dst, int weight) {
    if (!isValidEdge(src, dst)) throw std::out_of_range("Invalid edge");
    if (isEdgeExist(src, dst) || isEdgeExist(dst, src)) throw std::invalid_argument("Edge already exists.");
    addDirectedEdge(src, dst, weight);
    addDirectedEdge(dst, src, weight);
}

void Graph::removeEdge(int src, int dst) {
    if (!isEdgeExist(src, dst) && !isEdgeExist(dst, src))
        throw std::invalid_argument("Edge does not exist.");
    if (isEdgeExist(src, dst)) removeNode(src, dst);
    if (isEdgeExist(dst, src)) removeNode(dst, src);
}

void Graph::addDirectedEdge(int src, int dst, int weight) {
    Node* newNode = new Node{dst, weight, nullptr};

    if (!adjList[src]) {
        adjList[src] = newNode;
    } else {
        Node* curr = adjList[src];
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    if (weight < 0) howManyNegatives++;
}


bool Graph::isEdgeExist(int src, int dst) {
    Node* curr = adjList[src];
    while (curr) {
        if (curr->vertex == dst) return true;
        curr = curr->next;
    }
    return false;
}

void Graph::removeNode(int from, int toRemove) {
    Node* prev = nullptr;
    Node* curr = adjList[from];
    while (curr) {
        if (curr->vertex == toRemove) {
            if (curr->weight < 0) howManyNegatives--;
            if (prev) prev->next = curr->next;
            else adjList[from] = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool Graph::isValidVertex(int v) const {
    return v >= 0 && v < numVertices;
}

bool Graph::isValidEdge(int src, int dst) {
    return src != dst && isValidVertex(src) && isValidVertex(dst);
}

int Graph::getNumEdges() const {
    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        Node* curr = adjList[i];
        while (curr) {
            if (curr->vertex > i) count++;
            curr = curr->next;
        }
    }
    return count;
}

void Graph::getEdges(int** edgesArray, int& numEdges) const {
    numEdges = getNumEdges();
    *edgesArray = new int[numEdges * 3];
    int index = 0;
    for (int i = 0; i < numVertices; i++) {
        Node* curr = adjList[i];
        while (curr) {
            if (curr->vertex > i) {
                (*edgesArray)[index++] = i;
                (*edgesArray)[index++] = curr->vertex;
                (*edgesArray)[index++] = curr->weight;
            }
            curr = curr->next;
        }
    }
}

bool Graph::isNegative() {
    return howManyNegatives != 0;
}

void Graph::setDiscoveryOrder(int* order) {
    delete[] discoveryOrder;
    discoveryOrder = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        discoveryOrder[i] = order[i];
    }
}

void Graph::setParentArray(int* p) {
    delete[] parent;
    parent = new int[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = p[i];
    }
}

void Graph::printGraph() {
    std::cout << "\n===== Adjacency List " 
              << (discoveryOrder ? "(by discovery order)" : "") 
              << " =====\n";

    if (discoveryOrder) {
        // DEBUG: הצג את תוכן discoveryOrder
        std::cout << "Debug: discoveryOrder = [ ";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << discoveryOrder[i] << " ";
        }
        std::cout << "]\n\n";

        bool valid = true;

        // בדיקת תקפות הערכים
        for (int i = 0; i < numVertices; ++i) {
            int node = discoveryOrder[i];
            if (node < 0 || node >= numVertices) {
                std::cerr << "⚠️  Invalid discoveryOrder[" << i << "] = " << node << "\n";
                valid = false;
            }
        }

        if (!valid) {
            std::cerr << "\n❌ discoveryOrder contains invalid entries. Falling back to regular order.\n\n";
        }

        // הדפסת הרשימה לפי discoveryOrder אם תקין
        if (valid) {
            for (int i = 0; i < numVertices; ++i) {
                int node = discoveryOrder[i];
                std::cout << node << " → ";
                Node* curr = adjList[node];
                while (curr) {
                    std::cout << "(" << curr->vertex << ", " << curr->weight << ")";
                    if (curr->next) std::cout << " -> ";
                    curr = curr->next;
                }
                std::cout << std::endl;
            }
            return; // כבר הדפסנו, לא צריך המשך
        }
    }

    // fallback: הדפסת גרף רגילה
    for (int i = 0; i < numVertices; ++i) {
        std::cout << i << " → ";
        Node* curr = adjList[i];
        while (curr) {
            std::cout << "(" << curr->vertex << ", " << curr->weight << ")";
            if (curr->next) std::cout << " -> ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}


}