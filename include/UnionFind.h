#ifndef UNION_FIND_H
#define UNION_FIND_H

class UnionFind {
private:
    int* parent;
    int* rank;
    int size;

public:
    UnionFind(int n);
    ~UnionFind();

    int find(int node);
    void unionSet(int u, int v);
    bool isConnected(int u, int v);
};

#endif
