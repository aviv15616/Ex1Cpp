// Author: anksilae@gmail.com
#include <iostream>
#include "UnionFind.hpp"

UnionFind::UnionFind(int n) : size(n) {
    parent = new int[n];
    rank = new int[n];

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int node) {
    if (parent[node] != node) {
        parent[node] = find(parent[node]);  
    }
    return parent[node];
}

void UnionFind::unionSet(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

bool UnionFind::isConnected(int u, int v) {
    return find(u) == find(v);
}
void UnionFind::print() const {
    // מציג רק את הקבוצות המאוחדות בפועל
    bool* seen = new bool[size];
    for (int i = 0; i < size; ++i) seen[i] = false;

    std::cout << "Connected sets:\n";
    for (int i = 0; i < size; ++i) {
        int root = find(i);
        if (!seen[root]) {
            seen[root] = true;
            std::cout << "  Set " << root << ": { ";
            for (int j = 0; j < size; ++j) {
                if (find(j) == root) {
                    std::cout << j << " ";
                }
            }
            std::cout << "}\n";
        }
    }

    delete[] seen;
}


int UnionFind::find(int node) const {
    if (parent[node] != node) {
        // Note: נדרש cast כאן, כי אנחנו לא יכולים לשנות משתנה בקונסט
        return find(parent[node]);  // נניח שאתה לא עושה path compression במקרה הזה
    }
    return parent[node];
}
