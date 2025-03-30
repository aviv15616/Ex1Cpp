#include "UnionFind.h"

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