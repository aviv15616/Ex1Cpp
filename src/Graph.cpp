#include "Graph.h"
#include "Algorithms.h"
#include <iostream>
#include <stdexcept> 
#include <sstream>

namespace graph {

    Graph::Graph(int vertices) : numVertices(vertices) {
        adjList = new Node *[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Node *current = adjList[i];
            while (current) {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;  // ✅ Correct indentation
    }

    void Graph::addEdge(int src, int dst, int weight) {
        if (!isValidEdge(src, dst)) {
            std::ostringstream oss;
            oss << "Invalid edge: src = " << src << ", dst = " << dst 
                << " (vertices must be distinct and within [0, " << numVertices - 1 << "])";
            throw std::out_of_range(oss.str());
        }
        if (isEdgeExist(src, dst)) {
            std::ostringstream oss;
            oss << "Edge already exists between vertex " << src << " and vertex " << dst;
            throw std::invalid_argument(oss.str());
        }
        // Add edge src -> dst
        Node* newNode = new Node{dst, weight, adjList[src]};
        adjList[src] = newNode;

        // Add edge dst -> src (undirected graph)
        newNode = new Node{src, weight, adjList[dst]};
        adjList[dst] = newNode;
    }

    void Graph::removeEdge(int src, int dst) {
        if (!isValidEdge(src, dst)) {
            std::ostringstream oss;
            oss << "Invalid edge: src = " << src << ", dst = " << dst
                << " (vertices must be distinct and within [0, " << numVertices - 1 << "])";
            throw std::out_of_range(oss.str());
        }
        if (!isEdgeExist(src, dst)) {
            std::ostringstream oss;
            oss << "Edge doesn't exist between vertex " << src << " and vertex " << dst;
            throw std::invalid_argument(oss.str());
        }

        removeNode(src, dst);
        removeNode(dst, src);
    }
    
    void Graph::printGraph() {
        for (int i = 0; i < numVertices; i++) {
            Node* curr = adjList[i];
            std::cout << i << " →";  
            while (curr) {
                std::cout << " (" << curr->neighbor << ", " << curr->weight << ")";
                if (curr->next) std::cout << " ,"; 
                curr = curr->next;
            }
    
            std::cout << std::endl;
        }
    }

    bool Graph::isValidEdge(int src, int dst) {
        return !(src == dst || src >= numVertices || dst >= numVertices || src < 0 || dst < 0);
    }

    bool Graph::isEdgeExist(int src, int dst) {
        if (adjList[src] == nullptr) return false;  // Prevent segmentation fault
        Node* temp = adjList[src];
        while (temp) {
            if (temp->neighbor == dst) return true;
            temp = temp->next;
        }
        return false;
    }

    void Graph::removeNode(int from, int toRemove) {
        if (adjList[from] == nullptr) {
            std::ostringstream oss;
            oss << "Error: Attempted to remove node " << toRemove 
                << " from vertex " << from << ", but vertex " << from 
                << " has no edges.";
            throw std::runtime_error(oss.str());
        }
    
        Node* prev = nullptr;
        Node* curr = adjList[from];
    
        while (curr) {
            if (curr->neighbor == toRemove) {
                if (prev) {
                    prev->next = curr->next;  // Bypass current node
                } else {
                    adjList[from] = curr->next;  // If it's the head, update the head
                }
                delete curr;  // Free memory
                return;  // Exit immediately after deleting
            }
            prev = curr;
            curr = curr->next;
        }
    
        // If we reach here, the node was not found
        std::ostringstream oss;
        oss << "Error: Node " << toRemove << " not found in adjacency list of vertex " << from;
        throw std::invalid_argument(oss.str());
    }
    
}
