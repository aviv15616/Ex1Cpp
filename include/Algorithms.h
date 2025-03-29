#ifndef ALGORITHMS_H
#define ALGORITHMS_H


namespace graph{

    class Graph;

    class Algorithms{

    static Graph bfs(Graph& g, int start);
    static Graph dfs(Graph& g, int start);
    static Graph dijkstra(Graph& g, int start);
    static Graph prim(Graph& g, int start);
    static Graph kruskal(Graph& g, int start);

    };
}
#endif
